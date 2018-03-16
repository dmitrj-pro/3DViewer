#include "Viewer.h"
#include "ui_Viewer.h"
#include <QPen>
#include <QColor>

#define DAL 200

void Viewer::resetType(){
    ui->actionCentrOne->setChecked(false);
    ui->actionParallel->setChecked(false);
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

