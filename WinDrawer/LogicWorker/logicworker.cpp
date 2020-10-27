#include "logicworker.h"

LogicWorker::LogicWorker(QObject *parent)
    : QObject(parent)
{

    this->edit = new QLineEdit();

    this->firstLayout = new QHBoxLayout();
    this->firstLayout->addWidget(this->edit);

    this->secondLayout = new QHBoxLayout();
    this->thirdLayout = new QGridLayout();

    this->mainLayout = new QVBoxLayout();
    this->mainLayout->addLayout(this->firstLayout);
    this->mainLayout->addLayout(this->secondLayout);
    this->mainLayout->addLayout(this->thirdLayout);


    this->buttonActionArray.append(new QPushButton("="));
    this->buttonActionArray.append(new QPushButton("+"));
    this->buttonActionArray.append(new QPushButton("-"));
    this->buttonActionArray.append(new QPushButton("*"));
    this->buttonActionArray.append(new QPushButton("/"));
    this->buttonActionArray.append(new QPushButton("<"));
    this->buttonActionArray.append(new QPushButton("CE"));

    for(int i = 1; i <= 9; i++)
        this->buttonNumberArray.append(new QPushButton(QString::number(i)));
    this->buttonNumberArray.append(new QPushButton("0"));

    for(int i = 0; i < this->buttonActionArray.length() - 2; i++){
        this->buttonActionArray[i]->setMaximumWidth(40);
        this->secondLayout->addWidget(this->buttonActionArray[i]);
    }

    for(int i = 0, x = 0, y = 0; i < this->buttonNumberArray.length(); i++, y++){
        this->buttonNumberArray[i]->setMaximumWidth(40);
        this->thirdLayout->addWidget(this->buttonNumberArray[i], x, y);
        if(y == 4){
            y = -1;
            x++;
        }
    }

    this->buttonActionArray[5]->setMaximumWidth(40);
    this->buttonActionArray[6]->setMaximumWidth(40);
    this->thirdLayout->addWidget(this->buttonActionArray[6], 3, 0);
    this->thirdLayout->addWidget(this->buttonActionArray[5], 3, 1);

    QObject::connect(this->buttonActionArray[0], &QPushButton::clicked, [=]{this->characterType('=');});
    QObject::connect(this->buttonActionArray[1], &QPushButton::clicked, [=]{this->characterType('+');});
    QObject::connect(this->buttonActionArray[2], &QPushButton::clicked, [=]{this->characterType('-');});
    QObject::connect(this->buttonActionArray[3], &QPushButton::clicked, [=]{this->characterType('*');});
    QObject::connect(this->buttonActionArray[4], &QPushButton::clicked, [=]{this->characterType('/');});
    QObject::connect(this->buttonActionArray[5], &QPushButton::clicked, [=]{this->edit->setText(
                                            this->edit->text().left(this->edit->text().count() - 1));});
    QObject::connect(this->buttonActionArray[6], &QPushButton::clicked, [=]{this->edit->setText(QString());});

    for(int i = 1; i < this->buttonNumberArray.length(); i++)
        QObject::connect(this->buttonNumberArray[i-1], &QPushButton::clicked, [=]{this->characterType(i);});
    QObject::connect(this->buttonNumberArray.last(), &QPushButton::clicked, [=]{this->characterType(0);});
}

LogicWorker::~LogicWorker()
{
    delete this->edit;
    delete this->mainLayout;
    delete this;
}

QVBoxLayout* LogicWorker::getMainLayout(){
    return this->mainLayout;
}

void LogicWorker::characterType(char character)
{
    if(character == '=')
        calculate();
    else if(this->edit->text()[this->edit->text().length() - 1] == '+' ||
            this->edit->text()[this->edit->text().length() - 1] == '-' ||
            this->edit->text()[this->edit->text().length() - 1] == '*' ||
            this->edit->text()[this->edit->text().length() - 1] == '/')
        this->edit->setText(this->edit->text().left(this->edit->text().count() - 1) + character);
    else
        this->edit->setText(this->edit->text() + character);


}

void LogicWorker::characterType(int character)
{
    if(!this->edit->text().isEmpty() && character == 0)
        this->edit->setText(this->edit->text() + QString::number(character));
    else if(character != 0)
        this->edit->setText(this->edit->text() + QString::number(character));
}

void LogicWorker::calculate()
{
    QString text = this->edit->text();
    QVector<float> numbers;
    QVector<QChar> actions;

    QVector<QString> temp;
    temp.append(QString(""));

    for(int i = 0, y = 0; i < text.length(); i++)
    {
        if(text[i] == '+' || text[i] == '-' || text[i] == '*' || text[i] == '/'){
            actions.push_back(text[i]);
            y++;
            continue;
        }

        if(temp.length() <= y){
            temp.append(QString(text[i]));
            continue;
        }

        temp[y].append(text[i]);
    }

    for(int i = 0; i < temp.length(); i++)
    {
        numbers.push_back(temp[i].toInt());
    }

    float answer = this->calculate(numbers, actions);


    this->edit->setText(QString::number(answer));
}

float LogicWorker::calculate(QVector<float> numbers, QVector<QChar> actions)
{

    int i = 0, x = 0;
    while(actions.length() > 0)
    {
        if(i == actions.length() && x == 0){
            i = 0;
            x++;
        }

        if(x == 0 && actions[i] == '*'){
            numbers[i] *= numbers[i + 1];
            actions.remove(i);
            numbers.remove(i + 1);
            continue;
        }

        if(x == 0 && actions[i] == '/'){
            numbers[i] /= numbers[i + 1];
            actions.remove(i);
            numbers.remove(i + 1);
            continue;
        }

        if(x == 1 && actions[i] == '+'){
            numbers[i] += numbers[i + 1];
            actions.remove(i);
            numbers.remove(i + 1);
            continue;
        }

        if(x == 1 && actions[i] == '-'){
            numbers[i] -= numbers[i + 1];
            actions.remove(i);
            numbers.remove(i + 1);
            continue;
        }

        i++;
    }

    return numbers[0];
}

void LogicWorker::setMenuBar(QMenuBar *menuBar)
{
    this->mainLayout->setMenuBar(menuBar);
}
