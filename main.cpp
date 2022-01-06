#include "mainwindow.h"
#include <QApplication>
#include "welcomewindow.h"
#include "messagedialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
     * Initializing a welcome window and open it.
     */
    WelcomeWindow ww;
    ww.show();

    return a.exec();
}
