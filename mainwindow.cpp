#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connect(this,SIGNAL(customMousePressEvent()),this,SLOT(showmenu()));
    ui->setupUi(this);
}
/*
当发生一下情况时会产生绘制事件并调用paintEvent()函数:
1.在窗口部件第一次显示时，系统会自动产生一个绘图事件，从而强制绘制这个窗口部件。

2.当重新调整窗口部件的大小时，系统也会产生一个绘制事件。

3.当窗口部件被其他窗口部件遮挡，然后又再次显示出来的时候，就会对那些隐藏的区域产生一个绘制事件。

同时可以调用QWidget::update()或者QWidget::repaint()来强制产生一个绘制事件。二者的区别是:

repaint()函数会强制产生一个即时的重绘事件,而update()函数只是在Qt下一次处理事件时才调用一次绘制事件。

如果多次调用update(),Qt会把连续多次的绘制事件压缩成一个单一的绘制事件，这样可避免闪烁现象。
 */
void MainWindow::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QImage image;
    image.load(":/person.bmp");
    int w = image.width(); //横轴
    int h = image.height();//纵轴
    int neww,newh;

    //按比例进行图片缩放
    if(w>h){
        neww=900;
        newh=900*h/w;
    }
    else{
       neww=900*w/h;
       newh=900;
    }
    image = image.scaled(neww,newh,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    //根据图片大小设置窗口大小
    this->resize(QSize(neww,newh));
    this->setWindowTitle("请选取服装背景点和前景点");

    //窗口居中
    QDesktopWidget* desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);

    //绘制图片
    painter.drawImage(QPoint(0,0),image);
}

//鼠标右键事件 标记前景背景点
void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){

    }
    else if(event->button()==Qt::RightButton){
        //获取鼠标点击点坐标
        mouseposition = event->localPos();

        //触发信息槽 弹出菜单栏
        customMousePressEvent();
    }
}

void MainWindow::showmenu(){
    QMenu *menu = new QMenu(this);
    QAction *background = menu->addAction("背景点");
    QAction *foreground = menu->addAction("前景点");
    QAction *cancel = menu->addAction("取消");
    connect(background, SIGNAL(triggered(bool)), this, SLOT(addbackground()));
    connect(foreground, SIGNAL(triggered(bool)), this, SLOT(addforeground()));
    connect(cancel, SIGNAL(triggered(bool)), this, SLOT(cancel()));
    menu->exec(QCursor::pos());
}

void MainWindow::addbackground(){

}

void MainWindow::addforeground(){

}

void MainWindow::cancel(){

}

MainWindow::~MainWindow()
{
    delete ui;
}
