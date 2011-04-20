#ifndef GRID_H
#define GRID_H

#include <set>

class Creep;

class Grid {

    public:
        
        enum Direction {NONE, LEFT, RIGHT, UP, DOWN, 
                        TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT};

        Grid();
        ~Grid();

        void addCreep(Creep *creep);
        void removeCreep(Creep *creep);

        void setDirection(Direction dir);
        Direction getDirection() const;

        bool isOccupied() const;

    private:

        std::set<Creep *> _creeps;

        Direction _direction;

        bool _is_occupied;
};

#endif
