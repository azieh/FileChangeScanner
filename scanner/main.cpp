#include <QCoreApplication>

#include <QDir>
#include <iostream>


#include "dirscanner.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DirScanner ds;

    if ( !ds.initcycle ){
    ds.path = "c:\\totalcmd";
    ds.GetFileInfoList( ds.path, 0 );
    }





    return a.exec();
}

