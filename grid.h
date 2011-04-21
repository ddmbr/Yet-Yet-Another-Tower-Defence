#ifndef GRID_H
#define GRID_H

#include <set>

// Forward decalrations
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

        // Remove the tower from this grid
        void removeTower();

        // Set the direction which the creeps on this grid should head for
        void setDirection(Direction dir);

        // Get the direction
        Direction getDirection() const;

        // Set whether this grid is walkable by creeps
        void setWalkable(bool walkable);

        // Determine whether this grid is walkable
        bool isWalkable() const;

    private:

        std::set<Creep *> _creeps;
        Tower *_tower;

        Direction _direction;

        bool _is_walkable;
};

#endif
