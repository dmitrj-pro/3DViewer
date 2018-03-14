#include "Viewer.h"
#include "ui_Viewer.h"
#include <QPen>
#include <QColor>
#include "base_figure.h"

#define DAL 200

Viewer::Viewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Viewer){

    ui->setupUi(this);
    this->setCentralWidget(ui->verticalLayoutWidget);
    _img = new QGraphicsScene();
    ui->image->setScene(_img);


    this->connect(ui->element, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeObject(QString)));
    connect(ui->actionStatic, SIGNAL(triggered(bool)), this, SLOT(onStaticViewer(bool)));
    connect(ui->actionDinamic, SIGNAL(triggered(bool)), this, SLOT(onDinamicViewer(bool)));

    ui->element->addItem("Hexahedron");
    ui->element->addItem("Tetrahedron");
}

void Viewer::changeObject(QString str){
    if (str == "Tetrahedron")
        Tetrahedron(_figure);
    if (str == "Hexahedron")
        Hexahedron(_figure);
    Redraw();
}

void Viewer::onStaticViewer(bool){
    _type = TypeDraw::NONE;
    Redraw();
}

void Viewer::onDinamicViewer(bool){
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
