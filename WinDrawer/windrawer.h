#ifndef WINDRAWER_H
#define WINDRAWER_H

#include "LogicWorker/logicworker.h"
#include "WinAbout/winabout.h"

class WinDrawer : public QWidget //об'явлення об'єкту
{
    LogicWorker *logicworker;//об'єкт в об'єкті

    WinAbout *aboutWindow;

    QMenuBar *menuBar;

private slots:

    void showAbout();//функції в об'єкті

public:
    WinDrawer(QWidget *parent = nullptr);//конструктор об'єкту
    ~WinDrawer();//деструктор об'єкту
};

#endif // WINDRAWER_H
