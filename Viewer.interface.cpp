#include "Viewer.h"
#include "ui_Viewer.h"
#include "Viewer.BaseFigure.h"
#include <fstream>
#include <Types/Exception.h>


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

void Viewer::changeObject(QString str){
    ui->rotate_y_2->setValue(0);
    ui->rotate_x_2->setValue(0);
    ui->rotate_z_2->setValue(0);
    _prev_rotation = Point<int>();

    if (str == LANX(L_TETRAHEDRON))
        Tetrahedron(_figure);
    if (str == LANX(L_HEXAHEDRON))
        Hexahedron(_figure);
    Redraw();
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
