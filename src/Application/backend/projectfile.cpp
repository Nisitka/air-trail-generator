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
    headObj[RLS]   = "RLS";
    headObj[plane] = "PLANES";
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
    else dirNameFile = path;

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
        // Если такой файл уже существует
        if (QFileInfo::exists(path))
            QFile::remove(path);

        // Создаем новый файл проекта
        proFile = new QFile(path);
        if (proFile->open(QIODevice::ReadWrite))
        {
            // Приводим файл к стандартному виду
            QTextStream stream(proFile);
            QStringList strList = headObj.values();
            foreach (QString str, strList)
            {
                stream << str + "\n" << "!\n" << "  \n";
            }

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
    else dirNameFile = path;

    return isCreated;
}

void ProjectFile::findingPoint(int &first, int &last,
                               const QString &obj)
{
    first = -1;
    last  = -1;
    int idLine = 0;
    QTextStream in(proFile);
    QString str;

    // Считываем все строки из файла
    in.seek(0);
    bool headIsFound = false;
    while(!in.atEnd())
    {
        // Текущая строка
        str = in.readLine();

        // Только для не пустых строк
        if(!(str.size() == 0)){

            // Ищем заголовок блока
            if (containsTag(str, obj))
            {
                first = idLine;
                headIsFound = true;
            }

            // Ищем конец блока
            if (headIsFound) // если заголовок блока найден
            {
                if (containsTag(str, "!"))
                {
                    last = idLine;
                    break;
                }
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

bool ProjectFile::addData(typeObjects t, const QString &data)
{
    bool isAppend = false;
    QFile* newFile = nullptr;

    //
    if (proFile->isOpen())
    {
        // Считываем текущую информацию
        QStringList currentData;
        proFile->seek(0); // Перемещаемся обязательно в начало
        while (!proFile->atEnd())
            currentData.append(QString(proFile->readLine()));

        // Узнаем в каком промежутке находится нужная нам сущность
        int f; int l;
        findingPoint(f, l, headObj.value(t));

        // Добавляем данные во временный буфер
        currentData.insert(l, data + "\n"); // Строку добавляем в конец

        // Создаем копию файла проекта, который в случае удачной записи станет основным
        newFile = new QFile(tmpNameFile);
        if (newFile->open(QIODevice::ReadWrite))
        {
            // Пишем всю информацию уже с добавленной
            QTextStream stream(newFile);
            foreach (QString s, currentData)
                stream << s; // Не добаляем переход на новую строку, т.к. он уже есть

            // Если удалось записать всю информацию в новый файл,
            //      то делаем его основным
            if (newFile->flush()) // Записываем данные на диск
            {
                if (proFile->remove())
                {
                    delete proFile;

                    // Даем ему название исходного файла проекта
                    if (newFile->rename(dirNameFile))
                    {   // повторно открываем для работы с ним
                        if (newFile->open(QIODevice::ReadWrite))
                        {
                            // и только тогда можно считать его файлом проекта
                            proFile = (QFile*)newFile;
                            isAppend = true;
                        }
                        else
                            setError(openFile, "Не удалось открыть измененный файл проекта");
                    }
                    else
                        setError(renameFile, "Не удалось переименовать обновленный файл проекта, \
                                              файл проекта остался по следующему пути:" + newFile->fileName());
                }
                else
                {   // Если не удалось удалить старый файл с целью замены, то оставляем как было
                    setError(delFile, "не удалось удалить старый файл проекта");
                    newFile->remove();
                    delete newFile;
                }
            }
            else
                setError(writeData, "Не удалось записать данные во временный файл");
        }
        else
            setError(buildFile, "Не удалось создать временный файл проекта");
    }
    else // Если файл не удалось открыть
        setError(openFile, "Файл проекта закрыт");

    return isAppend;
}

void ProjectFile::setError(typeError t, const QString &info)
{
    codeError = t;
    infoError = info;
}

void ProjectFile::deleteData(const QString &path)
{

}

bool ProjectFile::containsTag(const QString &s, const QString &tag)
{
    return s == tag;
}

ProjectFile::~ProjectFile()
{
    if (proFile != nullptr)
    {
        proFile->close();
        delete proFile;
    }
}
