#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>

class Config
{
public:
    int id;
    QString key;
};

class FileManager : public QObject
{
    Q_OBJECT
public:
    FileManager(){}
    FileManager(QString iniPath, QString dataPath);
    ~FileManager();
    void setPath(QString iniPath, QString dataPath);
    QString iniPath();
    QString dataPath();
    Config getConfig();
    QStringList getList();
    QStringList getData(QString key);

protected:
    QString iniName;
    QString dataName;

signals:

};

#endif // FILEMANAGER_H
