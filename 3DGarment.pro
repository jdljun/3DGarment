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
    reader.cpp \
    mainwindow.cpp

HEADERS  += \
    reader.h \
    basic.h \
    mainwindow.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    image.qrc
