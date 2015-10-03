#include <QDir>
#include <QDirIterator>
#include <QDebug>

#include "dirscanner.h"




DirScanner::DirScanner()
{

    directoryinfo.setFilter ( QDir::AllEntries | QDir::Hidden | QDir::NoDotAndDotDot );
    directoryinfo.setSorting( QDir::Name | QDir::DirsFirst );
}


void DirScanner::GetFileInfoList(QString actualpath, int cmdpaintspacer)
{
    directoryinfo.setPath( actualpath );

    fileinfolist = directoryinfo.entryInfoList();

    foreach ( fileinfo, fileinfolist ){

        if ( !initcycle ){
            if ( fileinfo.isDir() ){
                _qwarningtext = HEIGHTSPACER + fileinfo.fileName() + WIDTHSPACER;
            } else {
                _qwarningtext = HEIGHTSPACER + fileinfo.fileName();
            }

            qWarning() << QString( "%1" ).arg( _qwarningtext, ( _qwarningtext.length() + cmdpaintspacer ) );

            _recurentspacer = ( cmdpaintspacer + _qwarningtext.length() - 3 ); // calculate space for each line in Tree of files
        }

        GetFileInfoList( fileinfo.absoluteFilePath(), _recurentspacer );

    }


}

void DirScanner::CheckFileInfoList()
{

}
