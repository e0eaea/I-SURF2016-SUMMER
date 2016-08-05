#-------------------------------------------------
#
# Project created by QtCreator 2016-07-07T11:29:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test_painter2
TEMPLATE = app


SOURCES += main.cpp\
    graphicsbezieritem.cpp \
    mainwindow.cpp \
    mygraphicbezier.cpp \
    mypoint.cpp \
    mygraphicsview.cpp \
    fitcurve.cpp

HEADERS  += \
    graphicsbezieritem.h \
    mainwindow.h \
    mygraphicbezier.h \
    mypoint.h \
    mygraphicsview.h \
    fitcurve.h

FORMS    += mainwindow.ui
