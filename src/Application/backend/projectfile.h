#ifndef PROJECTFILE_H
#define PROJECTFILE_H

#include <QFile>
#include <QMap>

// Класс по работе с файлом проекта
class ProjectFile
{
public:
    ProjectFile();
    ~ProjectFile();

    // Коды ошибок
    enum typeError{none, openFile, delFile, buildFile, renameFile,
                   writeData, readFile}; // и т.д.

    // Формат файла проекта
    static void format(QString& strFormat)
    {strFormat = ".txt";} // .proj

    // Типы объектов в файле проекта (должен соответсвовать их порядок)
    enum typeObjects {RLS, plane, map};
    QStringList tegsObject{"RLS", "PLANES", "MAPS"};

    // Выгрузить строковые данные из файла проекта
    void unloading(QStringList& stringsData, // куда выгружаем
                   typeObjects obj);         // что (по тегу)

    // Узнать последнию ошибку
    int lastError(QString& infoError) const;
    int lastError() const;

    // Открыть файл проекта
    bool open(const QString& path);

    // Закрыть файл проекта
    bool close();

    // Создать файл проекта (с заменой)
    bool create(const QString& path);

    // Добавить записть
    bool addData(typeObjects t,        // В какой заголовок
                 const QString& data); // Какую строчку

    // Удалить данные
    bool deleteData(typeObjects t,        // Категория данных
                    const QString& data); // Данные

private:

    //
    bool isOpen;

    //
    const QString tmpNameFile = "tmpPro.txt";

    //
    void setError(typeError t, const QString& info);

    //
    QString dirNameFile;

    // Теги-заголовки для сущностей, необходимых для проекта
    QMap<int,QString> headObj;

    // Узнать промежуток содержащий информацию об сущности
    void findingPoint(int& first, int& last, // номера строк промежутка
                      const QString& obj);   // тег сущност

    //
    bool containsTag(const QString& s, const QString& tag);

    // Ошибка
    int codeError;
    QString infoError;

    //
    int countRLS;

    //
    int countMap;

    //
    int /*first*//*, last,*/ dfirst, dlast;

    // Карта, которая была открыта последней
    QString lastOpenMap; // путь карты на ФС

    //
    QFile* proFile;
};

#endif // PROJECTFILE_H
