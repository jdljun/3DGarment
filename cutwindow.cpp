#include "cutwindow.h"
#include "ui_cutwindow.h"

cutwindow::cutwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cutwindow)
{
    ui->setupUi(this);
}

void cutwindow::paintEvent(QPaintEvent *){

}
cutwindow::~cutwindow()
{
    delete ui;
}
