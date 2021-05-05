/**
 * @file main.cpp
 * @author Filip Januška
 * Entry point of the program. Creates the application and Main Window of the application.
 */

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
