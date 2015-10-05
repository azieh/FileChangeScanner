#include <QCoreApplication>
#include <QDir>
#include <Qtimer>
#include "dirscanner.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DirScanner ds;
    ds.StartScanner("c:\\");


    return a.exec();
}

