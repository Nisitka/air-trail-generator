#ifndef DRAWAREATOOL_H
#define DRAWAREATOOL_H

#include <QMouseEvent>
#include <QCursor>
#include <QObject>

class areaDrawWidget;

class drawAreaTool: public QObject
{
    Q_OBJECT
signals:
    //
    void pickSignal(int id);

public slots:
    // Назначить инструмент выбранным
    void assign();

public:
    drawAreaTool(areaDrawWidget*, int id);

    enum keyMouse{left, right, mid};
    enum statusMouse{press, release};

    virtual void mousePress(QMouseEvent* mouse) = 0;
    virtual void mouseRelease(QMouseEvent* mouse) = 0;
    virtual void mouseMove(QMouseEvent* mouse) = 0;

    virtual void drawTask(QPainter& painter) = 0;

    virtual void wheelEvent(QWheelEvent *event);

    virtual void init();
    virtual void end() = 0;

    void getCoordMouse(int& idX, int& idY);

    int getStatMouse();
    int getLastKeyMouse();

protected:

    //
    void addButton(const QPixmap& pixButton, const QString& nameButton);

    void onButton();
    void offButton();

    //
//    QPixmap buttonImg;
//    QString nameButton;

    //
    QWidget* button;

    // ключ  инструмента в drawArea
    int id;

    // Получить дискреты карты
    void getCoordID(int& idX, int& idY);

    // кнопки
    static int lastKeyMouse;
    static int statMouse;

    // курсор
    static int xPressMouse; // последние координаты нажатия
    static int yPressMouse;
    static int xMouse;      // последние координаты
    static int yMouse;
    static int pXo;         // левый верх-й угол карты при нажатии/отпускании мыши
    static int pYo;

    //
    int idX, idY;
    double k;

    // к чему принадлежат инструменты
    areaDrawWidget* drawArea;

    //
    QCursor cursor;

private:

};

#endif // DRAWAREATOOL_H
