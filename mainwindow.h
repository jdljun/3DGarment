#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QPainter>
#include <QMouseEvent>
#include <basic.h>
#include <QListView>
#include <QMenu>
#include <QPointF>
#include <QMenu>
#include <map>
#include <QkeyEvent>
#include <grubcuter.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent* );
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent*);

private:
    Ui::MainWindow *ui;
    QImage image;
    QString windowtitle = "background and foreground select";
    QPointF mouseposition;

    //服装所处矩形框
    QPointF leftup;
    QPointF rightdown;

    multimap<int, int> tracepiexls;
    multimap<int, int> backgroundpiexls;
    multimap<int, int> foregroundpiexls;

private slots:
    void showmenu();
    void addbackground();
    void addforeground();
    void cancel();
signals:
    void customMousePressEvent();

};

#endif // MAINWINDOW_H
