#include "filemanager.h"
#include "global.h"
#include <QSettings>
#include <QDebug>

FileManager::FileManager(QString configPath, QString dataPath)
{
    setPath(configPath, dataPath);
}

void FileManager::setPath(QString configPath, QString dataPath)
{
    configName = configPath;
    dataName = dataPath;
}

QString FileManager::iniPath()
{
    return configName;
}

QString FileManager::dataPath()
{
    return dataName;
}

Config FileManager::getConfig()
{
    QSettings settings(configName, QSettings::IniFormat);
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
    data = qUncompress(data);

    QStringList list;
    int pos = data.indexOf(REF_END);
    list.append(pos == -1 ? "" : data.left(pos + 1).data());

    if(pos != -1) data.remove(0, pos + strlen(REF_END));
    data.replace("\\k", "\n");
    list.append(data.data());

    return list;
}

void FileManager::saveConfig(Config config)
{
    QSettings settings(configName, QSettings::IniFormat);
    settings.setValue(iniId, config.id);
    settings.setValue(iniKey, config.key);
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
