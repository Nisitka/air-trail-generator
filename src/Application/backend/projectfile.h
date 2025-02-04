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
    enum typeError{none, openFile, delFile, buildFile, renameFile, writeData}; // и т.д.

    //
    enum typeObjects {RLS, plane};

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

private:

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

    // Выгрузить строковые данные из файла проекта
    void unloading(QVector<QString>& stringsData, // куда выгружаем
                   typeObjects obj);              // что (по тегу)

    void deleteData(const QString& path);

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
