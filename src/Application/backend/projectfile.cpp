#include "projectfile.h"

#include <QFileInfo>
#include <QTextStream>
#include <QVector>
#include <QDebug>

ProjectFile::ProjectFile():
    proFile(nullptr),
    codeError(none)
{

    // Назначаем теги для сущностей
    headObj[RLS] = "RLS";
    headObj[plane] = "BPLA";
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
                QVector<QString> stringsVector;
                unloading(stringsVector, plane);
                isOpen = true;
                //findingPoint();
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

void ProjectFile::findingPoint(int &first, int &last,
                               const QString &obj)
{
    //----!Для подсчёта общего кол-ва строк!-----
    //    int line_count = 0;

    //    QString line[1000]; //???
    //    QTextStream in(proFile);
    //    while(!in.atEnd())
    //    {
    //        line[line_count]=in.readLine();
    //        line_count++;
    //    }

    //    qDebug() << line_count;
    //----------------------------------------

    //first = 0;
    //last = 0;
    int line_count = 0;
    QTextStream in(proFile);
    QString line[1000];
    QString str;

    //in.seek(0);
    while(!in.atEnd())
    {
        str = in.readLine();
        line_count++;

        if(!(str.size() == 0)){
            if (frontWith(str, obj))
            {
                first = line_count;
                qDebug() << first;
            }
            if (frontWith(str, "!"))
            {
                last = line_count;
                qDebug() << last;
                break;
            }
        }
    }
    //unloading();
}

void ProjectFile::unloading(QVector<QString>& stringsVector, typeObjects obj)
{
    int f,l;
    findingPoint(f,l,headObj.value(obj));
    QTextStream in(proFile);
    //QVector<QString> stringsVector;
    in.seek(0);
    QString str;
    for(int n = 1; n <= l;){

        while(!in.atEnd())
        {
            str = in.readLine();
            if(!(str.size() == 0)){
                if (n > f && n < l)
                {
                    stringsVector.push_back(str);
                }
            }
            n++;
        }
    }
    for (const QString& answer : stringsVector)
    {
        qDebug() << answer << endl;
    }
    proFile->close();

    //qDebug() << last - first - 2;
}

void ProjectFile::addData(const QString &path)
{
//    QStringList strList;
//    if ((proFile->exists()) && (proFile->open(QIODevice::ReadOnly)))
//    {
//        while (!proFile->atEnd())
//        {
//            strList << proFile->readLine();
//        }
//        proFile->close();
//    }
//    if ((proFile->exists()) && (proFile->open(QIODevice::WriteOnly)))
//    {
//        strList.insert(last - 2, ""+ path +"\n");
//        QTextStream stream(proFile);
//        foreach (QString s, strList)
//        {
//            stream << s;
//        }
//        proFile->close();
//    }
}

void ProjectFile::deleteData(const QString &path)
{
    proFile->open(QIODevice::ReadOnly);
    QTextStream in(proFile);
    QString line[1000];
    QString str;
    QStringList strList;
    in.seek(0);
    int line_count = 0;
    dfirst = 0;
    dlast = 0;

    while(!in.atEnd())
    {
        str = in.readLine();
        line_count++;

        if(!(str.size() == 0)){
            if (findString(str, "BPLA"))
            {
                dfirst = line_count;
                //qDebug() << dfirst;
            }
            if (findString(str, ""+ path +""))
            {
                dlast = line_count;
                //qDebug() << dlast;
                break;
            }
        }
    }

    proFile->close();

    if (proFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream edit(proFile);
        while (!edit.atEnd()) strList.push_back(edit.readLine());
    }
    proFile->close();

    strList.removeAt(dlast - 1);

    if (proFile->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream edit(proFile);
        for (int i=0; i<strList.size(); i++) edit << strList[i] << endl;
    }
    proFile->close();
}

bool ProjectFile::frontWith(const QString &s, const QString &suffix)
{
    return s.at(0) == suffix.at(0);
}

bool ProjectFile::findString(const QString &s, const QString &suffix)
{
    return s == suffix;
}

ProjectFile::~ProjectFile()
{
    if (proFile != nullptr)
    {
        proFile->close();
        delete proFile;
    }
}
