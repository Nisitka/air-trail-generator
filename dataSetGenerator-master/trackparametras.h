#ifndef TRACKPARAMETRAS_H
#define TRACKPARAMETRAS_H

#include <QObject>

class trackParametras : public QObject
{
    Q_OBJECT
public slots:
    void setE(double E_);

public:
    double* getE();

    trackParametras();

private:
    double E;
};

#endif // TRACKPARAMETRAS_H
