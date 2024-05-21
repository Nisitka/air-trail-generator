#ifndef SCROLLDIRECTOR_H
#define SCROLLDIRECTOR_H

class ScrollItem;

class ScrollDirector
{
public:
    ScrollDirector() { /* ... */ }

    //
    virtual void ItemChanged(ScrollItem* item) = 0;

protected:
    virtual void CreateItems() = 0;
};

#endif // SCROLLDIRECTOR_H
