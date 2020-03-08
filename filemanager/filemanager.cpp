#include "filemanager.h"
#include "global.h"
#include <QSettings>
#include <QDebug>

FileManager::FileManager(QString iniPath, QString dataPath)
{
    setPath(iniPath, dataPath);
}

void FileManager::setPath(QString iniPath, QString dataPath)
{
    iniName = iniPath;
    dataName = dataPath;
}

QString FileManager::iniPath()
{
    return iniName;
}

QString FileManager::dataPath()
{
    return dataName;
}

Config FileManager::getConfig()
{
    QSettings settings(iniName, QSettings::IniFormat);
    Config config;
    config.id = settings.value(iniId).toInt();
    config.key = settings.value(iniKey).toString();

    return config;
}

QStringList FileManager::getList()
{
    QSettings settings(dataName, QSettings::IniFormat);
    return settings.allKeys();
}

QStringList FileManager::getData(QString key)
{
    QSettings settings(dataName, QSettings::IniFormat);
    QByteArray data = settings.value(key.toUtf8().data()).toByteArray();
    data = qCompress(data);
    QStringList list;
    int pos = data.indexOf(REF_END);
    list.append(pos == -1 ? "" : data.left(pos + 1).data());
    data.remove(0, pos + strlen(REF_END));
    data.replace("\\k", "\n");
    list.append(data.data());
    return list;
}

void FileManager::saveData(QString key, QStringList list)
{
    QByteArray data;
    data.append(list[REF_POS]);
    data.append(list[CON_POS].replace("\n", "\\k"));
    data = qCompress(data);
    QSettings settings(dataName, QSettings::IniFormat);
    settings.setValue(key, data);
}

void FileManager::remove(QString key)
{
    QSettings settings(dataName, QSettings::IniFormat);
    settings.remove(key);
}

FileManager::~FileManager()
{
    qDebug() << "FileManager call destruction";
}
