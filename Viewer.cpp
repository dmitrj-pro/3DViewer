#include "Viewer.h"
#include "ui_Viewer.h"
#include <QPen>
#include <QColor>
#include "base_figure.h"
#include <fstream>
#include <Generator/CodeGenerator.h>
#include <Types/Exception.h>

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

void Viewer::LoadLang(){
    ui->menuImage->setTitle(LANX(L_IMAGE));
    ui->actionCentrOne->setText(LANX(L_IMG_CENTRAL));
    ui->actionParallel->setText(LANX(L_IMG_PARALLEL));
    ui->menuDraw_Type->setTitle(LANX(L_IMG_TYPE));

    ui->element->clear();
    ui->element->addItem(LANX(L_HEXAHEDRON));
    ui->element->addItem(LANX(L_TETRAHEDRON));

    ui->menuLang->setTitle(LANX(L_LANG));
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
