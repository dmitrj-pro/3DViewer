#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "figure.h"
#include <Parser/Setting.h>

#define CONFIG_FILE "3view.conf"

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
    void onParallelViewer(bool);
    void onCentrOneViewer(bool);
    void OnLangENG(bool);
    void OnLangRUS(bool);

private:
    void Redraw();
    void resetType();
    void LoadLang();
    void SaveSetting();
    void setLang(QString);

    DP::String LAN(const DP::String & str);
    QString LANX(const DP::String & str);
    Ui::Viewer *ui;
    QGraphicsScene * _img;
    TypeDraw _type = TypeDraw::Persp;
    Figure<double> _figure;

    DP::Setting _setting;
    DP::Setting _lang;
};

#endif // VIEWER_H
