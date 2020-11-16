#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QVector2D>
#include <solver.h>
#include <solverinterval.h>

class MyWidget: public QWidget
{
    Q_OBJECT

public:
    MyWidget();

private Q_SLOTS:
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
    SolverInterval* intervalSolver;

};

#endif // MYWIDGET_H
