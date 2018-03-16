#-------------------------------------------------
#
# Project created by QtCreator 2018-03-13T14:42:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraphicView
TEMPLATE = app

CONFIG += c++11

INCLUDEPATH += /home/INCLUDE/
LIBS += /home/INCLUDE/libdp.a

SOURCES += main.cpp\
        Viewer.cpp \
        Viewer.interface.cpp \
        Viewer.operation.cpp \
        Viewer.Drawer.cpp

HEADERS  += Viewer.h \
    Matrix.h \
    Point.h \
    Operation.h \
    Line.h \
    Figure.h \
    Viewer.BaseFigure.h

FORMS    += Viewer.ui
