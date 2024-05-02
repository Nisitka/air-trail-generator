#ifndef COORDS_H
#define COORDS_H


class Coords
{
public:
    Coords(int x, int y, int h);

    // Получить данные
    int X() const;
    int Y() const;
    int H() const;

private:

    int x;
    int y;
    int h;
};

#endif // COORDS_H
