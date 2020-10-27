#ifndef WINDRAWER_H
#define WINDRAWER_H

#include "LogicWorker/logicworker.h"
#include "WinAbout/winabout.h"

class WinDrawer : public QWidget
{
    LogicWorker *logicworker;

    WinAbout *aboutWindow;

    QMenuBar *menuBar;

private slots:

    void showAbout();

public:
    WinDrawer(QWidget *parent = nullptr);
    ~WinDrawer();
};

#endif // WINDRAWER_H
