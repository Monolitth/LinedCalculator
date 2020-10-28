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
    QObject::connect(this, &QWidget::destroyed, [=]{this->aboutWindow->hide();});
}

WinDrawer::~WinDrawer()
{
    delete this->logicworker;

    this->aboutWindow->hide(); //TODO: hide window if mainwindow hides
    delete this->aboutWindow;

    delete this;
}

void WinDrawer::showAbout()
{
    this->aboutWindow->show();
    this->aboutWindow->setWindowTitle("About");
    this->aboutWindow->setFixedSize(this->aboutWindow->sizeHint());
}
