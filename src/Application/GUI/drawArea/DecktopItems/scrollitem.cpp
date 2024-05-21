#include "scrollitem.h"

ScrollItem::ScrollItem(ScrollDirector* director):
    director(director)
{ /* ... */ }

void ScrollItem::Changed()
{
    director->ItemChanged(this);
}
