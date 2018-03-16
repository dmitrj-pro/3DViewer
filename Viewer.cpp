#include "Viewer.h"
#include "ui_Viewer.h"
#include <QPen>
#include <QColor>
#include "base_figure.h"
#include <fstream>
#include <Generator/CodeGenerator.h>
#include <Types/Exception.h>

#include <iostream>

#define DAL 200

#define SETTING_LANG "ui.lang"
#define SETTING_LANG_FILE "ui.lang_file"

#define L_TETRAHEDRON "base.Tetrahedron"
#define L_HEXAHEDRON "base.Hexahedron"
#define L_IMAGE "menu.image"
#define L_IMG_TYPE "menu.image.type"
#define L_IMG_PARALLEL "menu.image.parallel"
#define L_IMG_CENTRAL "menu.image.central-one"
#define L_LANG "menu.lang"

#define L_CONTROL_ROTATE_X "control.rotate_x"
#define L_CONTROL_ROTATE_Y "control.rotate_y"
#define L_CONTROL_ROTATE_Z "control.rotate_z"


void Viewer::LoadLang(){
    ui->menuImage->setTitle(LANX(L_IMAGE));
    ui->actionCentrOne->setText(LANX(L_IMG_CENTRAL));
    ui->actionParallel->setText(LANX(L_IMG_PARALLEL));
    ui->menuDraw_Type->setTitle(LANX(L_IMG_TYPE));

    ui->element->clear();
    ui->element->addItem(LANX(L_HEXAHEDRON));
    ui->element->addItem(LANX(L_TETRAHEDRON));

    ui->menuLang->setTitle(LANX(L_LANG));
    ui->rotate_x->setText(LANX(L_CONTROL_ROTATE_X));
    ui->rotate_y->setText(LANX(L_CONTROL_ROTATE_Y));
    ui->rotate_z->setText(LANX(L_CONTROL_ROTATE_Z));
}

inline void loadSetting(DP::Setting & res){
    std::ifstream read;
    read.open(CONFIG_FILE);
    #define ADD(NAME, DEFAULT) \
        if (!res.Conteins(NAME)) \
            res.add(NAME, DEFAULT);

    if (!read.fail()){
        read * res;
        read.close();
    }
    ADD(SETTING_LANG_FILE, "lang/ru.txt");
    ADD(SETTING_LANG, "RUS");
    #undef ADD
}

void Viewer::resetType(){
    ui->actionCentrOne->setChecked(false);
    ui->actionParallel->setChecked(false);
}

Viewer::Viewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Viewer){

    ui->setupUi(this);
    this->setCentralWidget(ui->verticalLayoutWidget);
    _img = new QGraphicsScene();
    ui->image->setScene(_img);


    this->connect(ui->element, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeObject(QString)));
    connect(ui->actionParallel, SIGNAL(triggered(bool)), this, SLOT(onParallelViewer(bool)));
    connect(ui->actionCentrOne, SIGNAL(triggered(bool)), this, SLOT(onCentrOneViewer(bool)));
    connect(ui->actionEng, SIGNAL(triggered(bool)), this, SLOT(OnLangENG(bool)));
    connect(ui->actionRus, SIGNAL(triggered(bool)), this, SLOT(OnLangRUS(bool)));
    connect(ui->rotate_x_2, SIGNAL(valueChanged(int)), this, SLOT(Rotete_x(int)));
    connect(ui->rotate_y_2, SIGNAL(valueChanged(int)), this, SLOT(Rotata_y(int)));
    connect(ui->rotate_z_2, SIGNAL(valueChanged(int)), this, SLOT(Rotata_z(int)));

    loadSetting(_setting);

    {
        std::ifstream read;
        read.open(_setting.get(SETTING_LANG_FILE));
        if (read.fail())
            throw EXCEPTION("Program is not installed. Reinstall it");
        read * _lang;
        read.close();
        if (_setting.get(SETTING_LANG) == "ENG")
            ui->actionEng->setChecked(true);
        if (_setting.get(SETTING_LANG) == "RUS")
            ui->actionRus->setChecked(true);
    }

    LoadLang();
}

void Viewer::SaveSetting(){
    std::ofstream os;
    os.open(CONFIG_FILE);
    os << _setting;
    os.close();
}

void Viewer::setLang(QString file){
    ui->actionEng->setChecked(false);
    ui->actionRus->setChecked(false);
    _setting.add(SETTING_LANG_FILE, file.toStdString());
    std::ifstream read;
    read.open(file.toStdString());
    if (read.fail())
        throw EXCEPTION("Program is not installed. Reinstall it");
    read * _lang;
    read.close();
    LoadLang();
    SaveSetting();
}

void Viewer::OnLangENG(bool){
    _setting.add(SETTING_LANG, "ENG");
    setLang("lang/eng.txt");
    ui->actionEng->setChecked(true);

}

void Viewer::OnLangRUS(bool){
    _setting.add(SETTING_LANG, "RUS");
    setLang("lang/ru.txt");
    ui->actionRus->setChecked(true);
}

void Viewer::changeObject(QString str){
    if (str == LANX(L_TETRAHEDRON))
        Tetrahedron(_figure);
    if (str == LANX(L_HEXAHEDRON))
        Hexahedron(_figure);
    Redraw();
}

#define PI 3.14159265358979323846

void Viewer::Rotete_x(int angle){
    _figure.RotateX(_prev_rotation.GetX() * (-1) *PI/180);
    _figure.RotateX(angle * PI / 180);
    _prev_rotation.SetX(angle);
    Redraw();
}

void Viewer::Rotata_y(int angle){
    _figure.RotateY(_prev_rotation.GetY() * (-1) *PI/180);
    _figure.RotateY(angle * PI / 180);
    _prev_rotation.SetY(angle);
    Redraw();
}

void Viewer::Rotata_z(int angle){
    _figure.RotateZ(_prev_rotation.GetZ() * (-1) *PI/180);
    _figure.RotateZ(angle * PI / 180);
    _prev_rotation.SetZ(angle);
    Redraw();
}


void Viewer::onParallelViewer(bool){
    resetType();
    ui->actionParallel->setChecked(true);
    _type = TypeDraw::NONE;
    Redraw();
}

void Viewer::onCentrOneViewer(bool){
    resetType();
    ui->actionCentrOne->setChecked(true);
    _type = TypeDraw::Persp;
    Redraw();
}

Viewer::~Viewer(){
    delete ui;
}

 void Viewer::resizeEvent(QResizeEvent* event){
     _img->deleteLater();
     _img = new QGraphicsScene(0, 0, size().width(), size().height());
     ui->image->setScene(_img);
     Redraw();
 }

template <typename T>
inline Point<T> ToPBPoint(const Point<T> & p, const T & w, const T & h){
    return Point<T> ((int) ((DAL * p.GetX() / (p.GetZ() + DAL)) + w/2), (int)((-1) * (DAL * p.GetY() / (p.GetZ() + DAL)) + h/2));
}

template <typename T>
inline Point<T> ToPBPoint1(const Point<T> & p, const T & w, const T & h){
    return Point<T> ((int)(p.GetX() + w/2), (int)((-1) * p.GetY() + h/2));
}

void Viewer::Redraw(){
    _img->clear();
    QPen pen(Qt::black);
    switch (_type){
            {
                case TypeDraw::NONE:
                auto lines = _figure.GetLines();
                for (auto x = lines.begin(); x != lines.end(); x++){
                    auto p1 = ToPBPoint1(x->GetStart(), _img->width(), _img->height());
                    auto p2 = ToPBPoint1(x->GetEnd(), _img->width(), _img->height());
                    _img->addLine(p1.GetX(), p1.GetY(), p2.GetX(), p2.GetY(), pen);
                }
            }
            break;
        case TypeDraw::Persp:
            {
                auto lines = _figure.GetLines();
                for (auto x = lines.begin(); x != lines.end(); x++){
                    auto p1 = ToPBPoint(x->GetStart(), _img->width(), _img->height());
                    auto p2 = ToPBPoint(x->GetEnd(), _img->width(), _img->height());
                    _img->addLine(p1.GetX(), p1.GetY(), p2.GetX(), p2.GetY(), pen);
                }
            }
            break;

    }

}

DP::String Viewer::LAN(const DP::String & X){
    if (!_lang.Conteins(X))  {
        DP::String str = "Key ";
        str += X + " is not found is lang file.";
        throw EXCEPTION(X);
    }
    return _lang.get(X);
}

QString Viewer::LANX(const DP::String & X){
    if (!_lang.Conteins(X))  {
        DP::String str = "Key ";
        str += X + " is not found is lang file.";
        throw EXCEPTION(X);
    }
    return QString::fromStdString(_lang.get(X));
}
