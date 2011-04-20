#ifndef COORD_H
#define COORD_H

struct Coord {
    Coord() {};
    Coord(int x, int y)
        :x(x), y(y) {}
    int x, y;
};

#endif
