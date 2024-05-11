#include "runwindow.h"

#include <QDebug>

runWindow::runWindow(QApplication* app_, const QString& dirFileImg)
{
    // инициализация изображения окна
    pix = new QPixmap(dirFileImg);

    // инициализация загрузочного экрана
    splashScreen = new QSplashScreen(*pix);

    //
    app = app_;

    splashScreen->show();
    app->processEvents();
}

void runWindow::updateProgress(int progress, const QString& textData)
{
    app->processEvents();

    QPainter painter;
    painter.begin(pix);

    painter.setBrush(QColor(155,238,100));
    painter.setPen(QPen(Qt::black));

    //
    painter.drawText(PROGRESS_X_PX, PROGRESS_Y_PX - 3 - PROGRESS_H_PX,
                     PROGRESS_W_PX, PROGRESS_H_PX,
                     1, "Пожалуйста, подождите...");

    //
    painter.drawRect(PROGRESS_X_PX, PROGRESS_Y_PX,
                     progress / 100.0 * PROGRESS_W_PX, PROGRESS_H_PX);

    splashScreen->setPixmap(*pix);

    painter.end();
}

void runWindow::close()
{
    splashScreen->close();

    //delete this; /// вылетает
}

runWindow::~runWindow()
{
    delete pix;
    delete splashScreen;
}
