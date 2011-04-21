#ifndef TOWER_H
#define TOWER_H

#include "coord.h"


// Abstract base tower class
class Tower {

    public:
        
        Tower();
        virtual ~Tower() = 0;

        // Attack the creep if the cooldown count has reached 0,
        // otherwise decrease the cooldown count
        virtual void attack() = 0;

        // Set the coordinate of this tower on the grid map
        // Note: this method should be called by GridMap
        void setCoord(Coord coord);

        // Set the cooldown (attack interval) of the tower
        void setCooldown(int cooldown);

        // Get the coordinate of this tower on the grid map
        Coord getCoord() const;

        void set 

    protected:

        Coord _coord; // coordinate of this tower on grid map

        int _cooldown;       // cooldown (attack interval)
        int _cooldown_count; // cooldown count
                             // the attack method will actually
                             // fire a bullet only when this count
                             // drops to zero
};

#endif
