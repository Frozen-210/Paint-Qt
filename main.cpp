#include "mainwindow.h"
#include <QApplication>
#include "welcomewindow.h"
#include "paintwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    WelcomeWindow ww;
    ww.show();

//    PaintWindow p;
//    p.show();

    return a.exec();
}
