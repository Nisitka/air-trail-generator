#ifndef SCROLLITEM_H
#define SCROLLITEM_H

#include "./scrolldirector.h"

// Объект, который взаимодействует с ScrollDirector
class ScrollItem
{
public:
    ScrollItem(ScrollDirector* director);

protected:
    void Changed();

private:
    ScrollDirector* director;
};

#endif // SCROLLITEM_H
