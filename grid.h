#ifndef GRID_H
#define GRID_H

#include <set>

class Creep;

class Grid {

    public:

        // enum the directions
        enum Direction {NONE, LEFT, RIGHT, UP, DOWN, 
                        TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT};

        Grid();
        ~Grid();

        // Add a creep to this grid
        void addCreep(Creep *creep);

        // Remove a creep from this grid
        void removeCreep(Creep *creep);

        // Set the direction which the creeps on this grid should
        // head for
        void setDirection(Direction dir);

        // Get the direction
        Direction getDirection() const;

        // Determine whether this grid is occupied by a tower
        bool isOccupied() const;

    private:

        std::set<Creep *> _creeps;

        Direction _direction;

        bool _is_occupied;
};

#endif
