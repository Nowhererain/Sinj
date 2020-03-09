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
    FileManager(QString configPath, QString dataPath);
    ~FileManager();
    void setPath(QString configPath, QString dataPath);
    QString iniPath();
    QString dataPath();
    Config getConfig();
    QStringList getList();
    QStringList getData(QString key);
    void saveConfig(Config config);
    void saveData(QString key, QStringList list);
    void remove(QString key);

protected:
    QString configName;
    QString dataName;

signals:

};

#endif // FILEMANAGER_H
