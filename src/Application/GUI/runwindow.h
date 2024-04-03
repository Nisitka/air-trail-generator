#ifndef RUNWINDOW_H
#define RUNWINDOW_H

#include <QObject>
#include <QApplication>

#include <QSplashScreen>
#include <QPainter>

// окно запуска приложения
class runWindow : public QObject
{
    Q_OBJECT
signals:

public slots:
    // Обновить значение полоски прогресса
    void updateProgress(int p,                    // Проценты готовности
                        const QString& textData); // Что загружается в тексте

    // закрыть окно
    void close();

public:
    runWindow(QApplication* app, const QString& dirFileImg);

    ~runWindow();

private:
    // Параметры полоски прогресса (относительно изображения)
    // левый верхний угол
    const int PROGRESS_X_PX = 339;
    const int PROGRESS_Y_PX = 449;
    // ширина высота
    const int PROGRESS_W_PX = 330;
    const int PROGRESS_H_PX = 26;

    // изображение окна загрузки
    QPixmap* pix;

    // загрузочный экран
    QSplashScreen* splashScreen;

    // приложение, загрузка которого проиходит
    QApplication* app;

};

#endif // RUNWINDOW_H
