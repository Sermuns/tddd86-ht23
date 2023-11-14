/**
 * TDDD86 Robots
 * By Daniel Alchasov (danal315) and Samuel Åkesson (samak519)
 */

#include <QApplication>
#include "mainwindow.h"
#include "utilities.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    rand_seed();     // seed random number generator

    MainWindow view; // create main window
    view.show();     // display main window

    return a.exec(); // start Qt event loop
}
