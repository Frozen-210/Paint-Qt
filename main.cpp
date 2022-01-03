#include "mainwindow.h"
#include <QApplication>
#include "welcomewindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WelcomeWindow ww;
    ww.show();

    return a.exec();
}
