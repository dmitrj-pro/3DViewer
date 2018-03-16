#include "Viewer.h"
#include "ui_Viewer.h"
#include <fstream>
#include <Types/Exception.h>


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

Viewer::~Viewer(){
    delete ui;
}

 void Viewer::resizeEvent(QResizeEvent* event){
     _img->deleteLater();
     _img = new QGraphicsScene(0, 0, size().width()/5*4, size().height());
     ui->image->setScene(_img);
     Redraw();
 }
