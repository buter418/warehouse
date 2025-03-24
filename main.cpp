#include <QApplication>
#include "mainwindow.h"
#include "product.h"
#include "product_list.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
