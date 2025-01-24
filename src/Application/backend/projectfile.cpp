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

    // Если существует такой путь
    if (QFileInfo::exists(path))
    {   // и он ведет к файлу
        if (QFileInfo(path).isFile())
        {   // и удалось закрыть предыдущий файл проекта
            if (this->close())
            {   // то пытаемся открыть файл
                proFile = new QFile(path);
                if (proFile->open(QIODevice::ReadWrite)){

                    /// --- Test --------------------
                    QVector<QString> stringsVector;
                    unloading(stringsVector, plane);
                    /// -----------------------------

                    isOpen = true;
                }
                else
                {
                    delete proFile;
                    infoError = "Не удалось открыть файл!";
                }
            }
            else
                infoError = "Не удалось закрыть предыдущий файл!";
        }
        else
            infoError = "Выбранный вами путь не является файлом!";
    }
    else
        infoError = "Выбранный вами путь несуществует!";

    // Если файл не удалось открыть, то сообщаем почему
    if (!isOpen) codeError = openFile; // код ошибки

    return isOpen;
}

bool ProjectFile::close()
{
    bool isClose = false;

    if (proFile != nullptr)
    {
        proFile->close();
        delete proFile;
    }
    isClose = true;

    return isClose;
}

bool ProjectFile::create(const QString &path)
{
    bool isCreated = false;

    //
    if (this->close())
    {
        proFile = new QFile(path);
        if (proFile->open(QIODevice::ReadWrite))
        {
            // Приводим файл к стандартному виду


            isCreated = true;
        }
        else
        {
            delete proFile;
            infoError = "Не удалось создать файл!";
        }
    }
    else
        infoError = "Не удалось закрыть предыдущий файл!";

    // Если файл не удалось создать файл, то сообщаем почему
    if (!isCreated) codeError = buildFile; // код ошибки

    return isCreated;
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

    first = -1;
    last  = -1;
    int idLine = 0;
    QTextStream in(proFile);
    QString str;

    // Считываем все строки из файла
    while(!in.atEnd())
    {
        // Текущая строка
        str = in.readLine();

        // Только для не пустых строк
        if(!(str.size() == 0)){

            // Ищем заголовок блока
            if (frontWith(str, obj))
            {
                first = idLine + 1;
                qDebug() << first;
            }

            // Ищем конец блока
            if (frontWith(str, "!"))
            {
                last = idLine - 1;
                qDebug() << last;
                break;
            }
        }

        //
        idLine++;
    }
}

void ProjectFile::unloading(QVector<QString>& stringsVector,
                            typeObjects obj)
{
    // Узнаем с какой и по какую строку содержится информация об сущности
    int f,l;
    findingPoint(f,l,
                 headObj.value(obj));

    //
    QTextStream in(proFile);
    QString str;

    // Доходим до нужной строки
    for (int i=0; i<(f-1); i++)
        in.readLine();

    // Считываем нужные (не пустые) строки
    for (int id=f; id<=l; id++)
    {
        // Очередная строка
        str = in.readLine();

        // Если строка не пустая, то добавляем её
        if (str.size() > 0)
            stringsVector.append(str);
    }

    /// --- Тестовый вывод нужных строк ---------
    for (const QString& answer : stringsVector)
    {
        qDebug() << answer << endl;
    }
    /// -----------------------------------------
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
