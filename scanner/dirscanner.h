#ifndef DIRSCANNER_H
#define DIRSCANNER_H
#include <QString>
#include <QDir>
#include <QDirIterator>


const QString WIDTHSPACER  = "--+";
const QString HEIGHTSPACER = " |+ ";

class DirScanner
{
public:

    DirScanner();


    void GetFileInfoList(QString actualpath, int cmdpaintspacer);
    void CheckFileInfoList();
    void PaintTreeInCmd();

    QString path;

    bool initcycle;

    QDir directoryinfo;
    QFileInfoList fileinfolist;
    QFileInfo fileinfo;

private:

    QString _qwarningtext;
    int _recurentspacer;


signals:

public slots:
};

#endif // DIRSCANNER_H
