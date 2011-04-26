#ifndef GRID_H
#define GRID_H

#include <set>


// Grid class, stores the information of the creeps or 
// tower on this grid
class Grid {

    public:

        // enum the directions
        enum Direction {NONE, LEFT, RIGHT, UP, DOWN, 
                        TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT};

        Grid();
        ~Grid();

        // Set the direction which the creeps on this grid should head for
        void setDirection(Direction dir);

        // Get the direction
        Direction getDirection() const;

        // Set whether this grid is walkable by creeps
        void setWalkable(bool walkable);

        // Determine whether this grid is walkable
        bool isWalkable() const;

    private:

        Direction _direction;

        bool _is_walkable;
};

#endif
