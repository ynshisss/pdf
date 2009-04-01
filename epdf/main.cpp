#include <QtGui/QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // read config file
//    globalParams = new GlobalParams ( "" );
//    globalParams-> setErrQuiet ( true );
    MainWindow w;
    w.setGeometry(100, 100, 600, 480);
    w.show();
    return a.exec();
}
