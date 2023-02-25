#ifndef PAINTERDATANETIMAGE_H
#define PAINTERDATANETIMAGE_H

#include "painterimage.h"

class painterDataNetImage : public painterImage
{
    Q_OBJECT
public slots:
    void run();

public:
    painterDataNetImage(Map*);

private:
    const double Pi = 3.1415926;

    double Kblue = 50;
};

#endif // PAINTERDATANETIMAGE_H
