#include "WinDrawer/windrawer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    WinDrawer drawer;
    drawer.setFixedSize(drawer.sizeHint());
    drawer.show();

    return app.exec();
}
