#ifndef SOLVER_H
#define SOLVER_H

#include <QString>
#include <QVector>
#include <cmath>
#include <cfenv>
#include <vector>

class Solver
{
public:
    Solver(QVector<QString> parameters);

    QString solve();


private:
    int Bairstow(int Stopien,double const *tabA, double *tabP,double *tabR, double eps, int N, double p_,double r_);
    //funkcje pomocnicze
    int PodzielWiel(int Stopien,double const *A, double p,double r, double *Q,double *R);
    int LiczMOdwrotna(double x,double y,double w,double z, double &a,double &b,double &c,double &d);

    int stopien;
    double *tabA;
    double *tabP;
    double *tabR;
};

#endif // SOLVER_H
