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
    void mousePressEvent(QMouseEvent *);

private:
    Ui::MainWindow *ui;
    QPointF mouseposition;

private slots:
    void showmenu();
    void addbackground();
    void addforeground();
    void cancel();
signals:
    void customMousePressEvent();

};

#endif // MAINWINDOW_H
