#ifndef HUMANVIEW_H
#define HUMANVIEW_H
#pragma once
#include <QObject>
#include <QtWidgets/QMainWindow>
#include<qopenglfunctions.h>
#include<qopenglwidget.h>
#include<qmatrix4x4.h>
#include<QKeyEvent>
#include<QWheelEvent>
#include<QMouseEvent>
#include <qevent.h>



class HumanView :  public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT

public:
    HumanView(QWidget* parent = nullptr, const char* path = "C:\\Users\\lenovo-pc\\Desktop\\3DGarment\\3DGarment\\body.obj");

    void keyPressEvent(QKeyEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

private:
    void transform();
private:
    float rotX = 0.0f;
    float rotY = 0.0f;
    float rotZ = 0.0f;
    float tranX = 0.0f;
    float tranY = 0.0f;
    float tranZ = 0.0f;
    float scale = 1.0f;

    QMatrix4x4 model, view, proj;

    unsigned int program;
    unsigned int VBO;
    unsigned int VAO;

    QVector<float> vertices;

};

#endif // HUMANVIEW_H
