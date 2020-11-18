QT += core gui widgets

TARGET = BairstowSolver
TEMPLATE = app
CONFIG += \
no_keywords

SOURCES += \
    main.cpp \
    mywidget.cpp \
    solver.cpp \
    solverinterval.cpp

HEADERS += \
    interval.h \
    mywidget.h \
    solver.h \
    solverinterval.h

LIBS +=\
    -L"/usr/local/boost/boost_1_55_0" \
    -L"/usr/include"


INCLUDEPATH +=\
    /usr/local/boost/boost_1_55_0 \
    /usr/include
