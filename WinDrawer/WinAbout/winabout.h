#ifndef WINABOUT_H
#define WINABOUT_H

#include <QtWidgets>

class WinAbout : public QWidget
{
private:

    QVBoxLayout *mainLayout;

    QLabel *header;
    QLabel *text;

public:
    explicit WinAbout(QWidget *parent = nullptr);

};

#endif // WINABOUT_H
