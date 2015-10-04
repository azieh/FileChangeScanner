#include <QDir>
#include <QDirIterator>
#include <QDebug>

#include "dirscanner.h"
#include <Qtimer>
#include <QDateTime>

DirScanner::DirScanner()
{

    directoryinfo.setFilter ( QDir::AllEntries | QDir::Hidden | QDir::NoDotAndDotDot );
    directoryinfo.setSorting( QDir::Name | QDir::DirsFirst );
}

void DirScanner::StartScanner()
{
    QTimer::singleShot(100, [=] { // cykliczne wywoływanie skanowania co 100ms
        GetFileInfoList( "d:\\", 0 );  // ustawiasz ścieszkę dostępu i 0 jest dla ustawień rysowania drzewa

        CheckForChanges(); // sprawdzanie zmian

        StartScanner(); // pentelka
    });
}

void DirScanner::GetFileInfoList(QString actualpath, int cmdpaintspacer)
{
    directoryinfo.setPath( actualpath );

    fileinfolist = directoryinfo.entryInfoList();

    foreach ( fileinfo, fileinfolist ){
        if ( !initcycle ){ // jezeli jestesmy w pierwszym cyklu to rysujemy drzewo
            if ( fileinfo.isDir() ){
                _qwarningtext = HEIGHTSPACER + fileinfo.fileName() + WIDTHSPACER;
            } else {
                _qwarningtext = HEIGHTSPACER + fileinfo.fileName();
            }
            qWarning() << QString( "%1" ).arg( _qwarningtext, ( _qwarningtext.length() + cmdpaintspacer ) );
            _recurentspacer = ( cmdpaintspacer + _qwarningtext.length() - 3 ); // calculate space for each line in Tree of files
        }

        map.insert( fileinfo.absoluteFilePath(), fileinfo.lastModified().toString("dd.MM.yy hh:mm:ss") );
        GetFileInfoList( fileinfo.absoluteFilePath(), _recurentspacer ); // rekurencja
    }
}


void DirScanner::CheckForChanges()
{
    if(initcycle){
        QHash<QString, QString>::iterator i;

        for (i = map.begin(); i != map.end(); ++i){
            QHash<QString, QString>::iterator j = backupmap.find(i.key());

            if (j == backupmap.end()){ // jezeli element mapy nie ma odpowiednika w backupie znaczy ze jest nowym plikiem
                qWarning() << QString("%1 %2 %3").arg(" ADD ", 10).arg(i.value(), 10).arg(i.key(), 10);
            }
            if (i == map.end()){ // chcialem analogicznie zrobić, że jeżeli backupie mapy jest element ktorego juz nie ma w mapie to znaczy ze plik został usunięty, ale to nie działa
                // jak zrobisz sobie debug to zobacz jakie wartosci ma iteroator i; j;
                qWarning() << QString("%1 %2 %3").arg(" DELETED ", 10).arg(i.value(), 10).arg(i.key(), 10);
            }
            while (j != backupmap.end() && j.key() == i.key()) { // iterowanie mapy w poszukiwaniu odpowiednika w backupie mapy
                if ( j.value() != i.value() ){                   // jezeli znalazlem te same klucze dostepu to porwonuje czas ich modyfikacji
                    qWarning() << QString("%1 %2 %3").arg(" MODIFIED ", 10).arg(i.value(), 10).arg(i.key(), 10);
                }
                j++;
            }
        }
    }
    backupmap=map; // po wykonaniu cyklu przezucam mape do backupu
    map.clear(); // czyszcze ja
    initcycle=true; // ustawiam po pierwszym cyklu bit zeby w pierwszym cyklu nie wykonywac porownania
}
