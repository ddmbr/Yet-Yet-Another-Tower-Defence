#include <cstdlib>

#include "grid.h"
#include "gridmap.h"


int main(int argc, char *argv[]) {
   
    GridMap *gm = new GridMap(30, 30);
    gm->setTarget(5, 5);
    gm->updateRoute();

#ifdef DEBUG
    gm->debugPrint();
#endif

    delete gm;

    return EXIT_SUCCESS;
}
