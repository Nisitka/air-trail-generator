#ifndef OPERATIONGLYPH_H
#define OPERATIONGLYPH_H

#include "glyph.h"
#include <QObject>

#include <QIcon>
#include <QMap>

#include <QComboBox>

class operationGlyph: public QObject, public Glyph
{
    Q_OBJECT
signals:

public:
    operationGlyph(QWidget* parent,
                   const QPoint& position, const QSize& size = QSize(20, 20));

    // Ключи операций
    enum Operations {sum, min, mul, div};

    // Узнать, какая сейчас выбрана операция
    int currentOperation() const; // key

protected:

    // Добавить операцию на выбор
    void addOperation(int key, const QIcon& icon);

    void draw(QPainter &painter);

    //
    void pressEvent(QMouseEvent* mouse) override;
    void releaseEvent(QMouseEvent* mouse) override;

    void missEvent() override;

    //
    void hoverEvent(QMouseEvent* mouse) override;

    //
    void moveEvent(QMouseEvent* mouse) override;

public slots:

    // Выбрать операцию
    void selectOperation(int id);

private:

    // Иконки операций
    QImage curOperIcon;              // выбранная (она же как и визуал)
    QMap <int, QImage> operPixIcons; // список возможных

    // Преобразует текущий id в ComboBox в key операции
    QMap <int, int> idToKey; // idItem, key
    int countOper; // кол-во добавленных операций

    //
    int curOperKey;

    //
    QComboBox* checkListWindow;

};

#endif // OPERATIONGLYPH_H
