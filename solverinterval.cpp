#include "solverinterval.h"

SolverInterval::SolverInterval(QVector<QString> Dane)
{

    this->stopien=Dane.length()-1;
    this->tabA=new interval_arithmetic::Interval<double>[stopien +1];
    this->tabP=new interval_arithmetic::Interval<double>[stopien/2 +1];
    this->tabR=new interval_arithmetic::Interval<double>[stopien/2 +1];
    //FE_TONEAREST;
    double pom1, pom2;

    //przypisanie do tablicy wartości
    for(int i=0; i<=stopien; i++)
    {
        pom1=Dane[i].toDouble();
        if(Dane[2*i]=="")
        {
            pom2=pom1;
        }
        else
        {
            pom2=Dane[2*i+1].toDouble();
        }
        //do sprawdzenia
        tabA[i]=interval_arithmetic::Interval<double>(pom1, pom2);
    }



}
