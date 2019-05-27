#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connect(this,SIGNAL(customMousePressEvent()),this,SLOT(showmenu()));

    image.load(":/image.jpg");
    ui->setupUi(this);
    cout<<"1"<<endl;
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
    this->setWindowTitle(windowtitle);

    //窗口居中
    QDesktopWidget* desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);

    //绘制图片
    painter.drawImage(QPoint(0,0),image);

    //画服装所在的矩形框
    painter.setPen(QPen(Qt::red,4));
    painter.drawRect(leftup.x(),leftup.y(),rightdown.x()-leftup.x(),rightdown.y()-leftup.y());

    //标记背景点（蓝色）和前景点（红色）
    multimap<int,int>::iterator it;
    for( it = backgroundpiexls.begin();it!=backgroundpiexls.end();it++){
        painter.setPen(Qt::blue);
        painter.setBrush(Qt::blue);
        painter.drawEllipse(QPointF(it->first,it->second),4,4);
    }
    for( it = foregroundpiexls.begin();it!=foregroundpiexls.end();it++){
        painter.setPen(Qt::red);
        painter.setBrush(Qt::red);
        painter.drawEllipse(QPointF(it->first,it->second),4,4);
    }

}

//鼠标右键事件 标记前景背景点
void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        leftup = event->localPos();
    }
    else if(event->button()==Qt::RightButton){
        //获取鼠标点击点坐标
        mouseposition = event->localPos();

        //触发信息槽 弹出菜单栏
       // customMousePressEvent();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event){
    if(event->buttons() & Qt::RightButton){
        QPointF p = event->localPos();
        tracepiexls.insert(pair<int,int>((int)p.x(),(int)p.y()));
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        rightdown = event->localPos();
        QWidget::update();
    }
    else if(event->button()==Qt::RightButton){
        customMousePressEvent();
    }

}

void MainWindow::keyPressEvent(QKeyEvent* event){

    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
        grubcuter GrubCuter(image,backgroundpiexls,foregroundpiexls,
                            (int)leftup.x(),(int)leftup.y(),
                            (int)rightdown.x()-(int)leftup.x(),(int)rightdown.y()-(int)leftup.y());
        image.load(QString::fromStdString(grubcutResultPath));
        initValue();
        QWidget::update();
    }
    //press y: grubcut result is ok
    if(event->key() == Qt::Key_Y){
        //当前窗口关闭
        this->hide();
        //进入到衣片分割的窗口
        cutwindow *cutWindow = new cutwindow(this);
        cutWindow->show();
    }
}

void MainWindow::showmenu(){
    QMenu *menu = new QMenu(this);
    QAction *background = menu->addAction("background piexls");
    QAction *foreground = menu->addAction("foreground piexls");
    QAction *cancel = menu->addAction("cancel");
    connect(background, SIGNAL(triggered(bool)), this, SLOT(addbackground()));
    connect(foreground, SIGNAL(triggered(bool)), this, SLOT(addforeground()));
    connect(cancel, SIGNAL(triggered(bool)), this, SLOT(cancel()));
    menu->exec(QCursor::pos());
}

void MainWindow::addbackground(){
    multimap<int,int>::iterator it;
    for( it = tracepiexls.begin();it!=tracepiexls.end();it++){
        backgroundpiexls.insert(pair<int,int>((int)it->first,(int)it->second));
    }
    tracepiexls.clear();
    QWidget::update();
}

void MainWindow::addforeground(){
    multimap<int,int>::iterator it;
    for( it = tracepiexls.begin();it!=tracepiexls.end();it++){
        foregroundpiexls.insert(pair<int,int>((int)it->first,(int)it->second));
    }
    tracepiexls.clear();
    QWidget::update();
}

void MainWindow::cancel(){
    tracepiexls.clear();
}

void MainWindow::initValue(){
    windowtitle = "grubcut result, press 'Y' next step";
    leftup.setX(0); leftup.setY(0);
    rightdown.setX(0);rightdown.setY(0);
    tracepiexls.clear();
    backgroundpiexls.clear();
    foregroundpiexls.clear();

}

MainWindow::~MainWindow()
{
    delete ui;
}
