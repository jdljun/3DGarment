#-------------------------------------------------
#
# Project created by QtCreator 2019-01-02T16:14:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3DGarment
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    reader.cpp \
    bmp.cpp

HEADERS  += mainwindow.h \
    reader.h \
    bmp.h

FORMS    += mainwindow.ui
