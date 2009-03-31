#include <QtGui/QApplication>
#include "mainwindow.h"
#include "xpdf/GlobalParams.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // read config file
//    globalParams = new GlobalParams ( "" );
//    globalParams-> setErrQuiet ( true );
    MainWindow w;
    w.show();
    return a.exec();
}
