#include <QCoreApplication>
#include <QDir>
#include <Qtimer>
#include "dirscanner.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DirScanner ds;

    ds.StartScanner(); // scieszke dostepu skanu ustawiasz w tym obiekcie
    return a.exec();
}

