#include "Viewer.h"


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
