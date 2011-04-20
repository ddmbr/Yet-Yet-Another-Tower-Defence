#ifndef COORD_H
#define COORD_H

struct Coord {
    Coord() {};
    Coord(unsigned x, unsigned y)
        :x(x), y(y) {}
    unsigned x, y;
};

#endif
