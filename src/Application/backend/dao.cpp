#include "dao.h"

QSqlDatabase db;

DAO::DAO()
{

}

void DAO::test_query(QString name)
{
    db = QSqlDatabase::addDatabase("QODBC3");
    db.setDatabaseName(QString("DRIVER={SQL SERVER}; SERVER=127.1.0.0; DATABASE="+ name +"; Trusted_Connection=yes;"));
    if(db.open())
    {
        QSqlQuery authentication;
        if (authentication.exec(QString("SELECT ID, nameAir FROM AirObjects ORDER BY nameAir ASC")))
        {
            while (authentication.next()){

            loading_AirInfo(authentication.value(0).toString(), authentication.value(1).toString());
            update_status(true);

            }
        }
    }else {
        db.close();
        db = QSqlDatabase();
        db.removeDatabase(QSqlDatabase::defaultConnection);
        update_status(false);
    }
}

void DAO::show_airInfo(QString ID)
{
    QSqlQuery authentication;
    airObj = new AirObject;
    if (authentication.exec(QString("SELECT nameAir, longAir, weightAir, speedAir, photoAir FROM AirObjects WHERE ID = '%1'")
                            .arg(ID)))
    {
        while (authentication.next()){

            airObj->setNameAir(authentication.value(0).toString());
            airObj->setLongAir(authentication.value(1).toDouble());
            airObj->setWightAir(authentication.value(2).toDouble());
            airObj->setSpeedAir(authentication.value(3).toDouble());
            airObj->setPhotoAir(authentication.value(4).toString());

//        show_airInfo(authentication.value(0).toString(),
//                     authentication.value(1).toDouble(),
//                     authentication.value(2).toDouble(),
//                     authentication.value(3).toDouble(),
//                     authentication.value(4).toString());
        }
    }
    show_AirObject(airObj);
}

void DAO::update_airInfo()
{
    QSqlQuery authentication;
    emit clearBoxs();
    if (authentication.exec(QString("SELECT ID, nameAir FROM AirObjects ORDER BY nameAir ASC")))
    {
        while (authentication.next()){

        loading_AirInfo(authentication.value(0).toString(), authentication.value(1).toString());

        }
    }
}

void DAO::creat_airInfo(QString n_Air, double l_Air, double w_Air, double s_Air, QString p_Air)
{
    QSqlQuery add_doc;
    qDebug() << n_Air << l_Air << w_Air << s_Air << p_Air;
    QString add_doc_text = QString("INSERT INTO AirObjects (nameAir, longAir, weightAir, speedAir, photoAir)\
            VALUES ('%1', %2, %3, %4,'%5');"
            ).arg(n_Air)
            .arg(l_Air)
            .arg(w_Air)
            .arg(s_Air)
            .arg(p_Air);
    if (!add_doc.exec(add_doc_text))
    {
        qWarning() << add_doc.lastError().databaseText();
    }

    update_airInfo();
}
