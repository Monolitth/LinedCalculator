#include "windrawer.h"

WinDrawer::WinDrawer(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("Lined Calculator");

    this->logicworker = new LogicWorker(this);

    this->aboutWindow = new WinAbout();

    this->setLayout(this->logicworker->getMainLayout());

    this->menuBar = new QMenuBar();
    this->menuBar->addAction("About");

    this->logicworker->setMenuBar(this->menuBar);

    QObject::connect(this->menuBar->actions().first(), &QAction::triggered, this, &WinDrawer::showAbout);
}

WinDrawer::~WinDrawer()
{
    delete this->logicworker;
    delete this;
}

void WinDrawer::showAbout()
{
    this->aboutWindow->show();
    //this->aboutWindow->setFixedSize(QSize(100, 100));
}
