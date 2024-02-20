#include "runwindow.h"

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

void runWindow::updateProgress(int progress)
{
    app->processEvents();

    QPainter painter;
    painter.begin(pix);

    painter.fillRect(
                PROGRESS_X_PX,
                PROGRESS_Y_PX,
                progress / 100.0 * PROGRESS_W_PX,
                PROGRESS_H_PX, QColor(155,238,100)
                );
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
