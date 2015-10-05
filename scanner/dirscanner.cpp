#include <QDir>
#include <QDirIterator>
#include <QDebug>

#include "dirscanner.h"
#include <Qtimer>
#include <QDateTime>

DirScanner::DirScanner() :
    _map ( nullptr ),
    _backupmap ( nullptr )
{
    _initcycle = true;
    _directoryinfo.setFilter ( QDir::AllEntries | QDir::Hidden | QDir::NoDotAndDotDot );
    _directoryinfo.setSorting( QDir::Name | QDir::DirsFirst );
}

DirScanner::~DirScanner()
{
    delete _map;
    _map = nullptr;

    delete _backupmap;
    _backupmap = nullptr;
}

void DirScanner::StartScanner(const QString actualpath)
{
    QTimer::singleShot(100, [=] { // cykliczne wywoływanie skanowania co 100ms
        _GetFileInfoList( actualpath, 0 );  // ustawiasz ścieszkę dostępu i 0 jest dla ustawień rysowania drzewa
        _CheckForChanges(); // sprawdzanie zmian
        StartScanner( actualpath ); // pentelka
    });
}

void DirScanner::_GetFileInfoList(QString actualpath, int cmdpaintspacer)
{
    if ( _map == nullptr ){
         _map = new QHash<QString, QString>;
    }
    _directoryinfo.setPath( actualpath );
    _fileinfolist = _directoryinfo.entryInfoList();

    foreach ( _fileinfo, _fileinfolist ){
        if ( _initcycle ){ // jezeli jestesmy w pierwszym cyklu to rysujemy drzewo
            if ( _fileinfo.isDir() ){
                _qdebugtext = HEIGHTSPACER + _fileinfo.fileName() + WIDTHSPACER;
            } else {
                _qdebugtext = HEIGHTSPACER + _fileinfo.fileName();
            }
            qDebug() << QString( "%1" ).arg( _qdebugtext,
                                           ( _qdebugtext.length() + cmdpaintspacer ) );
            _recurentspacer = ( cmdpaintspacer + _qdebugtext.length() - 3 ); // calculate space for each line in Tree of files
        } else { // koniec rysowania drzewa
            _recurentspacer = 0;
        }

        _map->insert( _fileinfo.absoluteFilePath(),
                      _fileinfo.lastModified().toString("dd.MM.yy hh:mm:ss") );

        _GetFileInfoList( _fileinfo.absoluteFilePath(), _recurentspacer ); // rekurencja
    }
}


void DirScanner::_CheckForChanges()
{
    if( !_initcycle ){
        QHash<QString, QString>::iterator i;

        for (i = _map->begin(); i != _map->end(); ++i){
            QHash<QString, QString>::iterator j = _backupmap->find(i.key());

            if (j == _backupmap->end()){ // jezeli element mapy nie ma odpowiednika w backupie znaczy ze jest nowym plikiem
                qDebug() << QString("%1 %2 %3").arg(" ADD ", 10).arg(i.value(), 10).arg(i.key(), 10);
            }
            if (i == _map->end()){ // chcialem analogicznie zrobić, że jeżeli backupie mapy jest element ktorego juz nie ma w mapie to znaczy ze plik został usunięty, ale to nie działa
                // jak zrobisz sobie debug to zobacz jakie wartosci ma iteroator i; j;
                qDebug() << QString("%1 %2 %3").arg(" DELETED ", 10).arg(i.value(), 10).arg(i.key(), 10);
            }
            while (j != _backupmap->end() && j.key() == i.key()) { // iterowanie mapy w poszukiwaniu odpowiednika w backupie mapy
                if ( j.value() != i.value() ){                   // jezeli znalazlem te same klucze dostepu to porwonuje czas ich modyfikacji
                    qDebug() << QString("%1 %2 %3").arg(" MODIFIED ", 10).arg(i.value(), 10).arg(i.key(), 10);
                }
                j++;
            }
        }
    }

    delete _backupmap;   //zwalnianie pamięci backupu
    _backupmap = nullptr; // zerowanie wskaźnika
    _backupmap=_map; // po wykonaniu cyklu przezucam wskaźnik z mapy do backupu
    _map = nullptr; // zerowanie wskaźnika do mapy

    _initcycle=false; // ustawiam po pierwszym cyklu bit zeby w pierwszym cyklu nie wykonywac porownania
}
