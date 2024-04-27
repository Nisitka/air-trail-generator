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
    DAO(); //Data Access Object
signals:
    void loading_AirInfo(QString, QString);
    void show_airInfo(QString,double,double,double,QString);
    void update_status(bool);
    void clearBoxs();

public slots:

    void test_query(QString);

    void show_airInfo(QString);

    void update_airInfo();

    void creat_airInfo(QString, double,double,double, QString);
private:

    QSqlQueryModel *model_nameAir = new QSqlQueryModel();
};

#endif // DAO_H
