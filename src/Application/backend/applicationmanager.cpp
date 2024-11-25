#include "applicationmanager.h"

#include <QFileInfo>
#include <QDataStream>
#include <QApplication>

ApplicationManager::ApplicationManager():
    maxCountLastProject(6),
    heightActionArea(300),
    widthActionArea(350)
{

    // Файл настроек лежит там же, где и  исполняемый файл
    const QString path = QApplication::applicationDirPath() + "settings.app";

    // Если файл такой уже существует, то
    if (QFileInfo::exists(path) && QFileInfo(path).isFile())
        initSettings(path);
    else
        createDefultSettings(path);
}

void ApplicationManager::initSettings(const QString& pathSettings)
{
    settingFile = new QFile(pathSettings);

    if (settingFile->open(QIODevice::ReadWrite))
    {
        // Записываем служебную информацию
        QByteArray data;
        QDataStream dStream(&data, QIODevice::ReadWrite);
        dStream << maxCountLastProject;
        dStream << widthActionArea;
        dStream << heightActionArea;
    }
    else
        error(readSettings, "Неудалось открыть файл настроек!");
}

void ApplicationManager::createDefultSettings(const QString& pathSettings)
{
    settingFile = new QFile(pathSettings);

    if (settingFile->open(QIODevice::ReadWrite))
    {
        // Считываем настройки

    }
    else
        error(createSettings, "Неудалось создать файл настроек!");
}
