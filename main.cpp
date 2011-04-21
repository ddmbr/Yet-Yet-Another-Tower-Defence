#define DEBUG

#include <cstdlib>

#include "coord.h"
#include "grid.h"
#include "gridmap.h"


int main(int argc, char *argv[]) {
   
    GridMap *gm = new GridMap(30, 30);
    gm->setTarget(Coord(5, 5));
    gm->updateRoute();
    gm->debugPrint();

    delete gm;

    return EXIT_SUCCESS;
}


