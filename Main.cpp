#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QLabel>
#include <QIcon>
#include <QLineEdit>
#include <stdlib.h>
#include "mywidget.h"
//using namespace std;

int main(int argc, char *argv[])
{
    QApplication program(argc, argv);

    QMainWindow window;


    auto rozw = new MyWidget();
    rozw->show();

    return program.exec();
}
