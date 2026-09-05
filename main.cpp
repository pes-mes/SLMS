#include <QApplication>
#include "mainwindow.h"
#include <QFontDatabase> // Mandatory header to register custom fonts
#include <QFont>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("MLCS MainWindow");
    MainWindow w;
    w.show();
    return a.exec();
}
