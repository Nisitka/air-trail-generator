#include "coords.h"

Coords::Coords():
    x(0), y(0), h(0), l(1)
{

}

Coords::Coords(int x, int y, int h, int l):
    x(x), y(y), h(h), l(l)
{

}

int Coords::longStep() const
{
    return l;
}

int Coords::X(units u) const
{
    switch (u) {
    case m:
        return x * l;
        break;
    case id:
        return x;
        break;
    }
}

int Coords::Y(units u) const
{
    switch (u) {
    case m:
        return y * l;
        break;
    case id:
        return y;
        break;
    }
}

int Coords::H(units u) const
{
    switch (u) {
    case m:
        return h * l;
        break;
    case id:
        return h;
        break;
    }
}
