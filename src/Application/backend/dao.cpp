#include "dao.h"

QSqlDatabase db;

DAO::DAO()
{

}

bool DAO::test_query(QString name)
{
    qDebug() << "test query!";

    db = QSqlDatabase::addDatabase("QODBC3");
    db.setDatabaseName(QString("DRIVER={SQL SERVER}; SERVER=127.1.0.0; DATABASE="+ name +"; Trusted_Connection=yes;"));
    if(db.open())
    {
        QSqlQuery authentication;
        if (authentication.exec(QString("SELECT test FROM Table_1")))
        {
            while (authentication.next()){

            qDebug() << authentication.value(0).toString();

            return 0;

            }
        }

        db.close();
        db = QSqlDatabase();
        db.removeDatabase(QSqlDatabase::defaultConnection);
    }

    return 1;
}
