#include "projectfile.h"

#include <QFileInfo>
#include <QTextStream>
#include <QVector>
#include <QDebug>

ProjectFile::ProjectFile():
    proFile(nullptr),
    codeError(none)
{
    proFile = new QFile("bd.txt");
    proFile->open(QIODevice::ReadOnly);
    dateFile();
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
            if (proFile->open(QIODevice::ReadWrite)){
                isOpen = true;
                dateFile();
            }
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

}

void ProjectFile::dateFile()
{
    int line_count = 0;

    QString line[10000]; //???
    QTextStream in(proFile);
    while(!in.atEnd())
    {
        line[line_count]=in.readLine();
        line_count++;
    }

    qDebug() << line_count;

    first = 0;
    last = 0;

    int line_count1 = 0;
    QString line1[10000];
    QString str;
    QVector<QString> stringsVector;

    in.seek(0);

    bool found = false;
    for(int n = 1; n <= line_count; n++){
        while(!in.atEnd())
        {
            str = in.readLine();

            line1[line_count1]=in.readLine();
            line_count1++;

            if (frontWith(str, "BPLA"))
            {
                first = line_count1;
                qDebug() << first;
            }

//            if (endsWith(str, "!BPLA"))
//            {
//                last = line_count1;
//                qDebug() << last;
//                found = true;
//                break;
//            }
        }

        if (found)
        {
            break;
        }
    }
}

ProjectFile::~ProjectFile()
{
    if (proFile != nullptr)
    {
        proFile->close();
        delete proFile;
    }
}

bool ProjectFile::frontWith(const QString &s, const QString &suffix)
{
    qDebug() << s.front() << suffix.front();
    return s.front() == suffix.front();
}

bool ProjectFile::endsWith(const QString &s, const QString &suffix)
{
    return s.front() == suffix.front();
}
