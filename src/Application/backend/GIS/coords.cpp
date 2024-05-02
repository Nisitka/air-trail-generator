#include "coords.h"

Coords::Coords(int x, int y, int h):
    x(x), y(y), h(h)
{

}

int Coords::X() const
{
    return x;
}

int Coords::Y() const
{
    return y;
}

int Coords::H() const
{
    return h;
}
