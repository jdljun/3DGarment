#ifndef DISPALY_H
#define DISPALY_H
#pragma once
#include "basic.h"
#include<qaction.h>
#include<qmenu.h>
#include<qmenubar.h>
#include <qmainwindow.h>
#include<qfiledialog.h>

class display :
    public QMainWindow
{
public:
    display();
    ~display();

private:
    QAction* openAct;
    QMenu* fileMenu;

public slots:
    void loadObj();
};


#endif // DISPALY_H
