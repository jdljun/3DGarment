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
    mainwindow.cpp \
    grubcuter.cpp \
    cutwindow.cpp

HEADERS  += \
    reader.h \
    basic.h \
    mainwindow.h \
    grubcuter.h \
    cutwindow.h

FORMS    += mainwindow.ui \
    cutwindow.ui

DISTFILES +=

CONFIG+=resources_big

RESOURCES += \
    image.qrc

INCLUDEPATH += D:\opencv\opencv\build\include\

INCLUDEPATH += D:\opencv\opencv\build\include\opencv\

INCLUDEPATH += D:\opencv\opencv\build\include\opencv2\

CONFIG(debug,debug|release) {
LIBS += -Ld:\opencv\opencv\build\x64\vc14\lib \
    -lopencv_core2413d \
    -lopencv_highgui2413d \
    -lopencv_imgproc2413d \
    -lopencv_features2d2413d \
    -lopencv_calib3d2413d
} else {
LIBS += -Ld:\opencv\opencv\build\x64\vc14\lib \
    -lopencv_core2413\
    -lopencv_highgui2413 \
    -lopencv_imgproc2413 \
    -lopencv_features2d2413 \
    -lopencv_calib3d2413
}

