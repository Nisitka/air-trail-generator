#ifndef BUILDERTRAIL_H
#define BUILDERTRAIL_H

#include <QObject>

class BuilderTrail: public QObject
{
    Q_OBJECT

signals:

    //
    void nextPointTrail(int idX, int idY, int idH);

public:
    BuilderTrail();
};

#endif // BUILDERTRAIL_H
