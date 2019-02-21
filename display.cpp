#include "display.h"
#include "humanview.h"

display::display()
{
    setCentralWidget(new HumanView);
    openAct = new QAction("open obj", this);
    fileMenu = menuBar()->addMenu(tr("&FIle"));
    fileMenu->addAction(openAct);
    connect(openAct, &QAction::triggered, this, &display::loadObj);
}

display::~display()
{
}

void display::loadObj() {
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Load Obj"), "C:\\Users\\lenovo-pc\\Desktop\\3DGarment\\3DGarment", tr("*.obj"));

    cout<<fileName.toStdString().c_str()<<endl;
    setCentralWidget( new HumanView( this, fileName.toStdString().c_str() ) );

    setFocus();
    centralWidget()->setFocus();

}
