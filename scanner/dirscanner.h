#ifndef DIRSCANNER_H
#define DIRSCANNER_H
#include <QString>
#include <QDir>
#include <QDirIterator>
#include <Qtimer>


const QString WIDTHSPACER  = "--+";
const QString HEIGHTSPACER = " |+ ";

class DirScanner : public QObject

{
public:

    DirScanner();
    ~DirScanner();

    void StartScanner(const QString actualpath);

private:
    void _GetFileInfoList(QString actualpath, int cmdpaintspacer);
    void _CheckForChanges();

    QHash<QString, QString>* _map,* _backupmap;
    QDir _directoryinfo;
    QFileInfoList _fileinfolist;
    QFileInfo _fileinfo;
    QString _qdebugtext;

    int _recurentspacer;
    bool _initcycle;


};

#endif // DIRSCANNER_H
