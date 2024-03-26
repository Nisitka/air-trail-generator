#ifndef DRAWTASK_H
#define DRAWTASK_H

#include <QPainter>
#include <QDebug>

#include <QVector>


struct taskPainter
{
    virtual void processing() = 0;
};

template <typename T>
class drawTask: public taskPainter
{
public:
    drawTask(T* object, void (T::*method)()): object(object), drawMethod(method){  }

    void processing() override
    {
        (object->*drawMethod)();
    }

private:
    //
    T* object;
    void (T::*drawMethod)();

};

#endif // DRAWTASK_H
