#include "solver.h"

Solver::Solver(QVector<QString> Dane)
{

    this->stopien=Dane.length()-1;
    this->tabA=new double[stopien +1];
    this->tabP=new double[stopien/2 +1];
    this->tabR=new double[stopien/2 +1];
    //FE_TONEAREST;

    //przypisanie do tablicy wartości z
    for(int i=0; i<=stopien; i++)
    {
        tabA[i]=Dane[i].toDouble();
    }



}

QString Solver::solve()
{
    int q=Bairstow(stopien, tabA, tabP, tabR, 0.00000000001, 1000, -1, -1);
            //precyzję ustawić na maksymalna - do obadania
            //100 iteracji, startowy trójmian: x^2+x+1

    if (q==1)
    {
        return "Za maly stopien wielomianu";
    }
    else if (q==2)
    {
        return "Uklad zależny - nie można znaleźć dzielnika";
    }
    else if (q==3)
    {
        return "Nie znaleziono dzielnika po maksymalnej ilosci iteracjach";
    }
    else if (q==0)//istnieje rozwiązaniE
    {
        QString result = "Współczynniki kolejnych dzielnikow kwadratowych: \n";
        for (int i=0;i<stopien/2;i++)
        {
            result+= QString::number(i)+") p=" +
                     QString::number(tabP[i], 'f', 10) + ", r=" +
                     QString::number(tabR[i], 'f', 10) + "\n";
        }
        return result;
    }
    return "";
}


int Solver::Bairstow(int Stopien,double const *tabA, double *tabP,double *tabR, double eps, int N, double p_,double r_)
/*Stopien - stopien wielomianu
 tabA - tablica wspolczynnikow
 tabP, tabR - tablice wspolczynnikow (p, r) trojmianow kwadratowych
 eps - dokladnosc pierwiastkow
 p,r - poczotkowe przyblizenie wspolczynnikow trojmianu
 N - max ilosc iteracji przy szukaniu dzielnika
*/
{
    int i,q, Iter, IndDziel=0;

    i=Stopien; //faktyczny stopien wielomianu 'tabA'
    while(i>=0 && tabA[i]==0)
    {
        i--;
    }

    if (i<2)
    {
        return 1;
    }

    std::vector<double> A(Stopien +1); //kopia wspolczynnikow
    for (i=0;i<=Stopien;i++)
    {
        A[i]=tabA[i];
    }

    std::vector<double> Q(Stopien-1 +1); //wynik dzielenia
    std::vector<double> W(Stopien-3 +1); //wynik dzielenia
    double Reszta[2]; //reszta z dzielenia
    double dqdp[2], dqdr[2];
    double p,r, a,b,c,d;

    while (Stopien>=2)
    {
        p=p_,r=r_; //poczotkowe dowolne wartosci
        Iter=0;
        do //----iteracja----
        {
            PodzielWiel(Stopien,A.data(),p,r,Q.data(),Reszta);
            //cout<<"Nr "<<Nrd<<") Reszta[1]="<<Reszta[1]<<", Reszta[0]="<<Reszta[0];
            //getchar();
            if (fabs(Reszta[1])<eps && fabs(Reszta[0])<eps)//czy reszta jest dostatecznie bliska 0.
            {
                break; //A dzieli si� przez tr�jmian (p,r) -ko�cz iteracj�
            }
   //Mam: Q,Reszta, p,r;   Licz� dqdp[], dqdr[]
            PodzielWiel(Stopien-2,Q.data(),p,r,W.data(),dqdr);
   //cout<<"2) dqdr[1]="<<dqdr[1]<<", dqdr[0]="<<dqdr[0]<<endl;
   //Pomnoz Q(x) przez x
            for (i=Stopien-2;i>=0;i--)
            {
                Q[i+1]=Q[i];
            }
            Q[0]=0;
   //Wypisz(Stopien-1,Q);
            PodzielWiel(Stopien-1,Q.data(),p,r,W.data(),dqdp);
   //cout<<"3) dqdp[1]="<<dqdp[1]<<", dqdp[0]="<<dqdp[0]<<endl;
   //-----------------
            q=LiczMOdwrotna(dqdp[0],dqdr[0],dqdp[1],dqdr[1],a,b,c,d);
            if (q==1)
            { //uklad zalezny;
                return 2;
            }
   //cout<<"a="<<a<<", b="<<b<<", c="<<c<<", d="<<d<<endl;
            p = p-(a*Reszta[0]+b*Reszta[1]);
            r = r-(c*Reszta[0]+d*Reszta[1]);
   //cout"p="<<p<<", r="<<r;
        }
        while (++Iter<N);

        if (Iter==N) return 3;

 //----Mam kolejny dzielnik (p,r)------
        tabP[IndDziel]=p;
        tabR[IndDziel]=r;
        IndDziel++;
 //----Podziel dany wielomian przez ten dzielnik, czyli 'A'='A'/(x^2 + px + r)-----
        Stopien-=2; //stopien zmniejszy sie o 2
        for (i=0;i<=Stopien;i++)
        {
            A[i]=Q[i];
        }
    } //koniec glownej p�tli

    return 0;
}

//funkcje pomocniczne
int Solver::PodzielWiel(int Stopien, double const * tabA, double p,double r, double *Q,double *R)
/*Stopien - stopien wielomianu
 A - tablica wspolczynnikow
 p,r - wspolczynniki trojmianu  x^2-px-r
 Q - wynikowa tablica wspolczynnikow ilorazu
 R - wynikowa tablica reszty
*/
{
    if (Stopien<0) return 1; //błąd

    int i;
    for (i=0;i<=Stopien-2;i++)
    {
        Q[i]=0; //wyzerowanie 'Q'
    }

    while (Stopien>=0 && tabA[Stopien]==0)
    {
        Stopien--; //ustawienie faktycznego stopnia wielomianu 'A'
    }

    if (Stopien<2)
    {
        R[0]=tabA[0];
        R[1]=tabA[1];
        return 0;
    }

    double *A=new double[Stopien +1]; //kopia wspolczynnikow
    for (i=0;i<=Stopien;i++)
    {
        A[i]=tabA[i];
    }

    Q[Stopien-2]=A[Stopien];
    if (Stopien>2)
    {
     //do sprawdzenia!
        //PodzielWiel(Stopien,A,p,r,Q,Reszta);

    /*
        Q[Stopien-3]=A[Stopien-1]+p*A[Stopien];
        for (i=Stopien-4;i>=0;i--)
        {
            Q[i]=A[i+2]+r*Q[i+2]+Q[i+1]*p;
        }
        R[1]=A[1]+p*Q[0]+r*Q[1];

        */
        for(i=Stopien; i>1; i--)
        {
            Q[i-2]=A[i];
            A[i-1]+=Q[i-2]*p;
            A[i-2]+=Q[i-2]*r;

        }
        R[1]=A[1];
        R[0]=A[0];

    }
    else
    {
        R[1]=A[1]+p*Q[0];
        R[0]=A[0]+r*Q[0];
    }
    delete[] A;
 return 0;
}

int Solver::LiczMOdwrotna(double x,double y,double w,double z, //dana macierz 2x2
                  double &a,double &b,double &c,double &d) //wynik macierz odwrotna do danej je�eli istnieje
{
    if (x*z==y*w)
    {
        return 1; //uk�ad zale�ny (wyznacznik zerowy)
    }
    if (x*w!=0)
    {
        c=1/(y-z*x/w);
        a=-z*c/w;
        d=1/(z-y*w/x);
        b=-y*d/x; //lub
    }
    else if (y*z!=0)
    {
        a=1/(x-w*y/z); c=-w*a/z;
        b=1/(w-z*x/y); d=-x*b/y; //lub b=1/(x-y*w/z);
    }
    else if (x==0 && z==0)
    {
        c=1/y;
        d=0;
        a=0;
        b=1/w;
    }
    else if (y==0 && w==0)
    {
        a=1/x;
        b=0;
        c=0;
        d=1/z;
    }
    return 0;
}
