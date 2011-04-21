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
        GridMap(int width, int height);

        // destructor
        ~GridMap();

        // Set the target coordinate of the this grid map
        // The target coordinate is where the creeps exit
        // note that x grows from left to right and
        // y grows from top to bottom.
        void setTarget(Coord coord);

        // Update the routes, this method is called each time
        // a new tower is built or a present tower is destroyed.
        void updateRoute();

        // Get the width of the map
        int getWidth() const;

        // Get the height of the map
        int getHeight() const;

#ifdef DEBUG
        void debugPrint() const;
#endif

    private:

    // helper functions

        // Clear all grids' directions and mark them as unvisited.
        // used in updateRoute()
        void clearGridsFlags(); 

        // Determine whether the given coordinate is valid
        bool isValidCoord(Coord coord); 
                                

    // data memebers

        // two dimensional array to hold the grids
        Grid **_grids;      

        // two dimensional array to hold the visit of the grids.
        // used in updateRoute;
        bool **_visited;    

        // width and height of the grid map
        int _width;    
        int _height;

        // coordinate of source grid
        Coord _target; 
};

#endif 
