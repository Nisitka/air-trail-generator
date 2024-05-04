#ifndef COORDS_H
#define COORDS_H


class Coords
{
public:
    Coords();
    Coords(int x, int y, int h,
           int longId); // В метрах

    enum units {m, id};

    // Получить данные
    int X(units u = m) const;
    int Y(units u = m) const;
    int H(units u = m) const;

    int longStep() const;

private:

    int x;
    int y;
    int h;

    int l;
};

#endif // COORDS_H
