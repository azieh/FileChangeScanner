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


    void GetFileInfoList(QString actualpath, int cmdpaintspacer);
    void StartScanner();
    void CheckForChanges();

    QHash<QString, QString> map, backupmap;
    QString path;

    bool initcycle=false;

    QDir directoryinfo;
    QFileInfoList fileinfolist;
    QFileInfo fileinfo;

private:

    QString _qwarningtext;
    int _recurentspacer;

};

#endif // DIRSCANNER_H
