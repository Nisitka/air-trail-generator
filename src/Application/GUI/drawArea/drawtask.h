#ifndef DRAWTASK_H
#define DRAWTASK_H

#include <QPainter>
#include <QDebug>

#include <QVector>


struct taskPainter
{
    virtual void processing(QPainter& painter) = 0;
};

template <typename T>
class drawTask: public taskPainter
{
public:
    drawTask(T* object, void (T::*method)(QPainter&)): object(object), drawMethod(method){  }

    void processing(QPainter& painter) override
    {
        (object->*drawMethod)(painter);
    }

private:
    //
    T* object;
    void (T::*drawMethod)(QPainter&);

};

#endif // DRAWTASK_H
