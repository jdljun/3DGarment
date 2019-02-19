#ifndef CUTWINDOW_H
#define CUTWINDOW_H

#include "basic.h"
#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QkeyEvent>
#include <QPointF>


namespace Ui {
class cutwindow;
}

class cutwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit cutwindow(QWidget *parent);
    ~cutwindow();
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent* );
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent*);

private:
    Ui::cutwindow *ui;

    QImage image;
    QString windowtitle = "Garment Panel Cut";

    multimap<int, int> tracepiexls;

    bool isfirstone;
    int* leftborder;
    int* rightborder;
};

#endif // CUTWINDOW_H
