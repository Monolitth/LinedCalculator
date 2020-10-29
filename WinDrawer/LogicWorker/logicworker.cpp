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
    this->buttonActionArray.append(new QPushButton("%"));
    this->buttonActionArray.append(new QPushButton("log"));

    for(int i = 1; i <= 9; i++)
        this->buttonNumberArray.append(new QPushButton(QString::number(i)));
    this->buttonNumberArray.append(new QPushButton("0"));

    for(int i = 0; i < this->buttonActionArray.length() - 4; i++){
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
    this->buttonActionArray[7]->setMaximumWidth(40);
    this->buttonActionArray[8]->setMaximumWidth(40);

    this->thirdLayout->addWidget(this->buttonActionArray[6], 3, 0);
    this->thirdLayout->addWidget(this->buttonActionArray[5], 3, 1);
    this->thirdLayout->addWidget(this->buttonActionArray[7], 3, 2);
    this->thirdLayout->addWidget(this->buttonActionArray[8], 3, 3);

    QObject::connect(this->buttonActionArray[0], &QPushButton::clicked, [=]{this->characterType('=');});
    QObject::connect(this->buttonActionArray[1], &QPushButton::clicked, [=]{this->characterType('+');});
    QObject::connect(this->buttonActionArray[2], &QPushButton::clicked, [=]{this->characterType('-');});
    QObject::connect(this->buttonActionArray[3], &QPushButton::clicked, [=]{this->characterType('*');});
    QObject::connect(this->buttonActionArray[4], &QPushButton::clicked, [=]{this->characterType('/');});
    QObject::connect(this->buttonActionArray[5], &QPushButton::clicked, [=]{this->edit->setText(
                                            this->edit->text().left(this->edit->text().count() - 1));});
    QObject::connect(this->buttonActionArray[6], &QPushButton::clicked, [=]{this->edit->setText(QString());});
    QObject::connect(this->buttonActionArray[7], &QPushButton::clicked, [=]{this->characterType('%');});
    QObject::connect(this->buttonActionArray[8], &QPushButton::clicked, [=]{this->characterType('l');});

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

    else if(character == 'l'){
        this->edit->setText(this->edit->text() + "log(");
        this->logTyped = true;
    }

    else if(this->edit->text()[this->edit->text().length() - 1] == '+' ||
            this->edit->text()[this->edit->text().length() - 1] == '-' ||
            this->edit->text()[this->edit->text().length() - 1] == '*' ||
            this->edit->text()[this->edit->text().length() - 1] == '/' )
        this->edit->setText(this->edit->text().left(this->edit->text().count() - 1) + character);

    else if(this->logTyped && this->edit->text()[this->edit->text().length() - 1].isDigit())
        this->edit->setText(this->edit->text() + ')' + character);

    else if(this->logTyped && !this->edit->text()[this->edit->text().length() - 1].isDigit())
        this->edit->setText(this->edit->text().left(this->edit->text().count() - 4) + character);

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

void LogicWorker::fillNumbersAndActions(QVector<float> *numbers, QVector<QChar> *actions)
{
    QString text = this->edit->text();
    QVector<QString> temp;

    bool isLog = false;
    bool isDigit = false;
    int y = -1;

    while(text.length() != 0)
    {
        if(isDigit && text[0].isDigit()){
            temp[y].append(text[0]);
            text.remove(0, 1);
        }

        else
            isDigit = false;

        if(isLog && text[0] == ')'){
            text.remove(0, 1);
            isLog = false;
        }

        else if(text[0].isDigit()){
            isDigit = true;
            temp.append(QString(text[0]));
            y++;
            text.remove(0, 1);
        }

        else if(text[0] == '*' || text[0] == '/' || text[0] == '+' || text[0] == '-' || text[0] == '%'){
            actions->append(text[0]);
            text.remove(0, 1);
        }

        else if(text[0] == 'l'){
            actions->append('l');
            text.remove(0, 4);
            isLog = true;
        }
    }

    for(int i = 0; i < temp.length(); i++)
    {
        numbers->push_back(temp[i].toInt());
    }
}

void LogicWorker::calculate()
{
    QVector<float> numbers;
    QVector<QChar> actions;

    this->fillNumbersAndActions(&numbers, &actions);

    float answer = this->calculate(numbers, actions);


    this->edit->setText(QString::number(answer));
}

float LogicWorker::calculate(QVector<float> numbers, QVector<QChar> actions)
{

    int i = 0, x = 0;
    while(actions.length() > 0)
    {
        if(i == actions.length() && (x == 0 || x == 1)){
            i = 0;
            x++;
        }

        if(x == 0 && actions[i] == '%'){
            numbers[i] /= 100;
            actions.remove(i);
            continue;
        }

        if(x == 0 && actions[i] == 'l'){
            numbers[i] = qLn(numbers[i]) / qLn(2);
            actions.remove(i);
            continue;
        }

        if(x == 1 && actions[i] == '*'){
            numbers[i] *= numbers[i + 1];
            actions.remove(i);
            numbers.remove(i + 1);
            continue;
        }

        if(x == 1 && actions[i] == '/'){
            numbers[i] /= numbers[i + 1];
            actions.remove(i);
            numbers.remove(i + 1);
            continue;
        }

        if(x == 2 && actions[i] == '+'){
            numbers[i] += numbers[i + 1];
            actions.remove(i);
            numbers.remove(i + 1);
            continue;
        }

        if(x == 2 && actions[i] == '-'){
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
