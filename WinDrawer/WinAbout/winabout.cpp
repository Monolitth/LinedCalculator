#include "winabout.h"

WinAbout::WinAbout(QWidget *parent) : QWidget(parent)
{
    this->mainLayout = new QVBoxLayout();

    this->header = new QLabel();
    this->header->setText("LineEdit Calculator 0.6");
    this->header->setStyleSheet("font-size: 25px; font-style: italic");

    this->text = new QLabel("Based on Qt 5.15.1\nCreated by Vladislav Varpihovsky");
    this->text->setStyleSheet("font-size: 20px;");

    this->mainLayout->addWidget(this->header);
    this->mainLayout->addWidget(this->text);


    this->setLayout(this->mainLayout);
}
