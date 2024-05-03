#ifndef AIROBJECT_H
#define AIROBJECT_H

#include <QObject>

class AirObject : public QObject
{
    Q_OBJECT
public:
    explicit AirObject(QObject *parent = nullptr);

signals:

public slots:

    QString getNameAir();
    double getLongAir();
    double getWightAir();
    double getSpeedAir();
    QString getPhotoAir();

    void setNameAir(QString);
    void setLongAir(double);
    void setWightAir(double);
    void setSpeedAir(double);
    void setPhotoAir(QString);

public:

    QString nameAir;
    double longsAir;
    double wightAir;
    double speedAir;
    QString photoAir;

};

#endif // AIROBJECT_H
