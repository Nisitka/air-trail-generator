#include "projectfile.h"

#include <QFileInfo>

ProjectFile::ProjectFile():
    proFile(nullptr),
    codeError(none)
{

}

int ProjectFile::lastError(QString &infoError_) const
{
    infoError_ = infoError;

    return lastError();
}

int ProjectFile::lastError() const
{
    return codeError;
}

bool ProjectFile::open(const QString &path)
{
    bool isOpen = false;

    //
    if (QFileInfo::exists(path))
    {
        if (QFileInfo(path).isFile())
        {
            proFile = new QFile(path);
            if (proFile->open(QIODevice::ReadWrite))
                isOpen = true;
            else
                infoError = "Не удалось открыть файл!";
        }
        else
            infoError = "Выбранный вами путь не является файлом!";
    }
    else
        infoError = "Выбранный вами путь несуществует!";

    // Если файл не удалось открыть, то сообщаем почему
    if (!isOpen) codeError = openFile;

    return isOpen;
}

void ProjectFile::create(const QString &path)
{
    /* ... */
}

ProjectFile::~ProjectFile()
{
    if (proFile != nullptr)
    {
        proFile->close();
        delete proFile;
    }
}
