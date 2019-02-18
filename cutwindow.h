#ifndef CUTWINDOW_H
#define CUTWINDOW_H

#include <QMainWindow>
#include <QPainter>

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

private:
    Ui::cutwindow *ui;
};

#endif // CUTWINDOW_H
