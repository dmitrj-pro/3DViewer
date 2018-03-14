#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "figure.h"

namespace Ui {
class Viewer;
}

class Viewer : public QMainWindow
{
    Q_OBJECT

public:
    enum class TypeDraw{NONE, Persp, Persp_Ots};
    explicit Viewer(QWidget *parent = 0);
    ~Viewer();

public slots:
    void changeObject(QString str);
    void resizeEvent(QResizeEvent* event);
    void onStaticViewer(bool);
    void onDinamicViewer(bool);

private:
    void Redraw();
    Ui::Viewer *ui;
    QGraphicsScene * _img;
    TypeDraw _type = TypeDraw::Persp;
    Figure<double> _figure;
};

#endif // VIEWER_H
