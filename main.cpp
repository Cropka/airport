#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    //w.setMaximumSize(900, 900);
    w.show();
    return a.exec();
}
