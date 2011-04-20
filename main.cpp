#define DEBUG

#include <cstdio>
#include <cstdlib>

#include "grid.h"
#include "gridmap.h"


int main(int argc, char *argv[]) {
   
    GridMap *gm = new GridMap(30, 30);
    gm->setTarget(2, 2);
    gm->updateRoute();
    gm->debugPrint();

    return EXIT_SUCCESS;
}

