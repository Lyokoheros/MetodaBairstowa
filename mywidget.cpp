#include "mywidget.h"
#include <solver.h>


MyWidget::MyWidget()
{
    degreeWindow = new QVBoxLayout();
    degree = new QSpinBox;
    buttonFP = new QPushButton("Zwykła");
    buttonIN = new QPushButton("Przedziałowa");

    degree->setMinimum(1);

    degreeWindow->addWidget(degree);
    degreeWindow->addWidget(buttonFP);
    degreeWindow->addWidget(buttonIN);


    connect(buttonFP, &QPushButton::clicked, this, [this](bool) {getParameters(degree->value(), false);});
    connect(buttonIN, &QPushButton::clicked, this, [this](bool) {getParameters(degree->value(), true);});
    //QObject::connect(&button, SIGNAL(clicked()), this, SLOT(getParameters(degree->value())))
}

void MyWidget::getParameters(int n, bool interval)
{
    delete layout();
    qDeleteAll(this->children());

    parametersWindow = new QGridLayout(this);
    button = new QPushButton("solve");
    QLineEdit* lineEdit;
    QString solution="tu będzie rozwiązanie";

    parameters.clear();
    if(!interval)
    {
        for (int i=0; i<=n; i++)
        {
            lineEdit = new QLineEdit(); //QString::number(i+1)
            parameters.push_back(lineEdit);
            parametersWindow->addWidget(new QLabel("X^"+QString::number(i)), 0, i);
            parametersWindow->addWidget(lineEdit, 1, i);
        }
        parametersWindow->addWidget(button, 2, 0);


        connect(button, &QPushButton::clicked, this, [this](bool) {
            this->solver = new Solver(prepareDoubles(parameters));
            parametersWindow->addWidget(new QLabel(solver->solve()), 3, 1);
            /*
            QString sol="Współczynniki: ";
            int i, n=4;
            double A[5];
            double Q[3];
            double p=-1, r=-2;
            A[4]=1; A[3]=4; A[2]=12; A[1]=13; A[0]=14;
            Q[2]=0; Q[1]=0; Q[0]=0;
            for(i=n; i>1; i--)
            {
                Q[i-2]=A[i];
                A[i-1]+=Q[i-2]*p;
                A[i-2]+=Q[i-2]*r;
                sol+= QString::number(Q[i-2]) + "  ";
            }
            sol+="Reszta:" + QString::number(A[1]) + "x+" + QString::number(A[0]);

            parametersWindow->addWidget(new QLabel(sol), 3, 1);
*/
        });
    }
    else
    {
        parametersWindow->addWidget(new QLabel("początek przedziału"), 1, 0);
        parametersWindow->addWidget(new QLabel("koniec przedziału"), 2, 0);
        for (int i=0; i<=n; i++)
        {
            parametersWindow->addWidget(new QLabel("X^"+QString::number(i)), 0, i+1);
            lineEdit = new QLineEdit();
            parameters.push_back(lineEdit);
            parametersWindow->addWidget(lineEdit, 1, i+1);
            lineEdit = new QLineEdit();
            parameters.push_back(lineEdit);
            parametersWindow->addWidget(lineEdit, 2, i+1);
        }
        parametersWindow->addWidget(button, 3, 1);

        connect(button, &QPushButton::clicked, this, [this](bool) {
            this->intervalSolver = new SolverInterval(prepareDoubles(parameters));
            parametersWindow->addWidget(new QLabel(intervalSolver->solve()), 3, 1);
        });


    }
   // parametersWindow->addWidget(new QLabel(solution), 4, 1);
}

QVector<QString> MyWidget::prepareDoubles(QVector<QLineEdit*> input)
{
    int n = input.length();
    QVector<QString> values;
    values.clear();
    for(int i=0; i<n; i++)
    {
        values.append(input[i]->text());
    }

    return values;
}
