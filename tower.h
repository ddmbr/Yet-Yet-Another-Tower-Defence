#ifndef TOWER_H
#define TOWER_H

#include <set>

// Abstract base tower class
class Tower {

    public:
        
        Tower();
        virtual ~Tower();

        // Return the creep if the cooldown count has reached 0,
        // otherwise decrease the cooldown count
//        virtual bool attack() = 0;

        // Set the coordinate of this tower on the grid map
        // Note: this method should only be called by GridMap
//        void setCoord(int x, int y);

        // Set the attack range of this tower
        void setRange(int range);

        // Set the cooldown (attack interval) of the tower
        void setCooldown(int cooldown);

        // Get the x and y coordinates of this tower on the grid map
        int getX() const;
        int getY() const;

    protected:

        int _x, _y;          // x and y coordinates

        int _range;

        int _cooldown;       // cooldown (attack interval)
        int _cooldown_count; // cooldown count
                             // the attack method will actually
                             // fire a bullet only when this count
                             // drops to zero
};

#endif
