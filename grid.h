#ifndef GRID_H
#define GRID_H

#include <set>

class Creep;
class Tower;

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

        // Add a tower to this grid
        void addTower(Tower *tower);

        // Remove a tower from this grid
        void removeTower(Tower *tower);

        // Set the direction which the creeps on this grid should head for
        void setDirection(Direction dir);

        // Get the direction
        Direction getDirection() const;

        // Determine whether this grid is occupied by a tower
        bool isOccupied() const;

    private:

        std::set<Creep *> _creeps;
        std::set<Tower *> _towers;

        Direction _direction;

        bool _is_occupied;
};

#endif
