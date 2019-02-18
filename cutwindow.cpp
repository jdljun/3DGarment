#include "cutwindow.h"
#include "ui_cutwindow.h"

cutwindow::cutwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cutwindow)
{
    ui->setupUi(this);
    image.load(QString::fromStdString(grubcutResultPath));

    //width = x  height = y
    leftborder = new int[image.height()];
    rightborder = new int[image.height()];

    isfirstone =true;
}

void cutwindow::paintEvent(QPaintEvent *){
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

    //绘制分割线
    for(int i=0;i<image.height();i++){
        painter.setPen(Qt::red);
        painter.setBrush(Qt::red);
        painter.drawEllipse(QPointF(leftborder[i],i),2,2);

    }

    for(int i=0;i<image.height();i++){
        painter.setPen(Qt::blue);
        painter.setBrush(Qt::blue);

        painter.drawEllipse(QPointF(rightborder[i],i),2,2);
    }

}

void cutwindow::mouseMoveEvent(QMouseEvent* event){
    if(event->buttons() & Qt::LeftButton){
        QPointF p = event->localPos();
        tracepiexls.insert(pair<int,int>((int)p.x(),(int)p.y()));
    }
}

void cutwindow::mouseReleaseEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        if(isfirstone){
            multimap<int,int>::iterator it;
            for( it = tracepiexls.begin();it!=tracepiexls.end();it++){
                leftborder[(int)it->second]=(int)it->first;
            }
            tracepiexls.clear();
            isfirstone=false;
        }
        else{
            multimap<int,int>::iterator it;
            for( it = tracepiexls.begin();it!=tracepiexls.end();it++){
                rightborder[(int)it->second]=(int)it->first;
            }
            tracepiexls.clear();
            isfirstone=true;
        }
        QWidget::update();
    }
}

void cutwindow::keyPressEvent(QKeyEvent* event){
    //重画分割线
    if(event->key() == Qt::Key_Escape){
        for(int i = 0; i<image.height();i++){
            leftborder[i]=-2;
            rightborder[i]=-2;
        }
        QWidget::update();
    }

    //进行分割
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
        //将分割线补充完整

        //分割，生成3部分
    }
}


cutwindow::~cutwindow()
{
    delete ui;
}
