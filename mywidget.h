#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVector2D>
#include <solver.h>

class MyWidget: public QWidget
{
    Q_OBJECT

public:
    MyWidget();

private slots:
    void getParameters(int n, bool interval);

    QVector<QString> prepareDoubles(QVector<QLineEdit*> input);


private:
    QGridLayout* parametersWindow;
    QVBoxLayout* degreeWindow;
    QSpinBox* degree;
    QPushButton* button;
    QPushButton* buttonFP;
    QPushButton* buttonIN;
    QVector<QLineEdit*> parameters;
    Solver* solver;


    //QVector2D<QString*> intervalValues;
};

#endif // MYWIDGET_H
