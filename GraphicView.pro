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

INCLUDEPATH += /INCLUDE/
LIBS += /INCLUDE/libdp.a

SOURCES += main.cpp\
        Viewer.cpp

HEADERS  += Viewer.h \
    matrix.h \
    point.h \
    2doperation.h \
    line.h \
    figure.h \
    base_figure.h

FORMS    += Viewer.ui
