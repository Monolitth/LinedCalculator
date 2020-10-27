#include "winabout.h"

WinAbout::WinAbout(QWidget *parent) : QWidget(parent)
{
    this->header = new QLabel(this);
    this->header->setText("LineEdit Calculator 0.6");
    this->header->setStyleSheet("font-size: 15px; font-style: italic");
}
