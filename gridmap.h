#ifndef GRIDMAP_H
#define GRIDMAP_H

#include "coord.h"

#define DEBUG

// Forward declaration to Grid class
class Grid;


// GridMap class
// Holds a two-dimensional array of grids and calculates
// the routes of the creeps.
class GridMap {
    
    public:

        // GridMap constructor, takes two params namely the 
        // width and height of the map
        GridMap(unsigned width, unsigned height);

        // destructor
        ~GridMap();

        // Set the target coordinate of the this grid map
        // The target coordinate is where the creeps exit
        // note that x grows from left to right and
        // y grows from top to bottom.
        void setTarget(unsigned x, unsigned y);

        // Update the routes, this method is called each time
        // a new tower is built or a present tower is destroyed.
        void updateRoute();

        // Get the width of the map
        unsigned getWidth() const;

        // Get the height of the map
        unsigned getHeight() const;

#ifdef DEBUG
        void debugPrint() const;
#endif

    private:

        // helper functions
        void clearGridsFlags(); // Clear all grids' directions
                                // and mark them as unvisited.
                                // used in updateRoute()

        bool isValidCoord(int x, int y); // Determine whether the given
                                         // coordinate is valid
                                

        // data memebers
        Grid **_grids;      // two dimensional array to hold the grids
        bool **_visited;    // two dimensional array to hold the visit
                            // of the grids.
                            // used in updateRoute;

        unsigned _width;    // width of grid map
        unsigned _height;   // height of grid map

        Coord _target;      // coordinate of source grid
};

#endif 
