#ifndef VISUALMAP3D_H
#define VISUALMAP3D_H

#include <QObject>

#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtGui/QScreen>
#include <QtGui/QPainter>

#include "backend/map.h"

class visualMap3D : public QObject
{
    Q_OBJECT
public:
    visualMap3D(QWidget* widget,
                int idXo, int idYo,
                int numW, int numL, Map* map_);

    ~visualMap3D();
private:

    Map* map;
};

#endif // VISUALMAP3D_H
