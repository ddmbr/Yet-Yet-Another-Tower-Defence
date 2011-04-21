#ifndef TOWER_H
#define TOWER_H

#include "coord.h"

// Abstract base tower class
class Tower {

    public:
        
        Tower();
        virtual ~Tower();

        virtual void attack() = 0;

    protected:

        Coord _coord;
};

#endif
