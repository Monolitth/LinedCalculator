#ifndef LOGICWORKER_H
#define LOGICWORKER_H

#include <QtWidgets>

class LogicWorker : public QObject
{
private:
    QLineEdit *edit;
    QHBoxLayout *firstLayout;
    QHBoxLayout *secondLayout;
    QGridLayout *thirdLayout;
    QVBoxLayout *mainLayout;


    QVector<QPushButton*> buttonActionArray;
    QVector<QPushButton*> buttonNumberArray;

    float calculate(QVector<float> numbers, QVector<QChar> actions);

private slots:

    void characterType(int  character);
    void characterType(char character);
    void calculate();
    void editChop();

public:
    LogicWorker(QObject *parent);
    ~LogicWorker();

    QVBoxLayout* getMainLayout();

    void setMenuBar(QMenuBar* menuBar);
};

#endif // LOGICWORKER_H
