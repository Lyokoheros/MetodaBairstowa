#ifndef SOLVERINTERVAL_H
#define SOLVERINTERVAL_H

#include <QString>
#include <QVector>
#include <cmath>
#include <cfenv>
#include "interval.h"


class SolverInterval
{
public:
    SolverInterval(QVector<QString> parameters);

    QString solve();


private:
    int Bairstow(int Stopien,
                 interval_arithmetic::Interval<double> *tabA,
                 interval_arithmetic::Interval<double> *tabP,
                 interval_arithmetic::Interval<double> *tabR,
                 double eps, int N,
                 interval_arithmetic::Interval<double> p_,
                 interval_arithmetic::Interval<double> r_);
    //funkcje pomocnicze
    int PodzielWiel(int Stopien,
                    interval_arithmetic::Interval<double> *A,
                    interval_arithmetic::Interval<double> p,
                    interval_arithmetic::Interval<double> r,
                    interval_arithmetic::Interval<double> *Q,
                    interval_arithmetic::Interval<double> *R);
    int LiczMOdwrotna(interval_arithmetic::Interval<double> x,
                      interval_arithmetic::Interval<double> y,
                      interval_arithmetic::Interval<double> w,
                      interval_arithmetic::Interval<double> z,
                      interval_arithmetic::Interval<double> &a,
                      interval_arithmetic::Interval<double> &b,
                      interval_arithmetic::Interval<double> &c,
                      interval_arithmetic::Interval<double> &d);

    int stopien;
    interval_arithmetic::Interval<double> *tabA;
    interval_arithmetic::Interval<double> *tabP;
    interval_arithmetic::Interval<double> *tabR;
};

#endif // SOLVERINTERVAL_H
