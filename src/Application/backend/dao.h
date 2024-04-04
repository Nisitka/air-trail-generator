#ifndef DAO_H
#define DAO_H
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlTableModel>

class DAO : public QObject
{
    Q_OBJECT
public:
    DAO();
public slots:

    void test_query();
};

#endif // DAO_H
