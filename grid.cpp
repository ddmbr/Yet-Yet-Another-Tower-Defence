#include "grid.h"

Grid::Grid()
    :_is_occupied(false) {
     
}

Grid::~Grid() {

}

void Grid::addCreep(Creep *creep) {
    _creeps.insert(creep);
}

void Grid::removeCreep(Creep *creep) {
    _creeps.erase(creep);
}

void Grid::addTower(Tower *tower) {
    _towers.insert(tower);
}

void Grid::removeTower(Tower *tower) {
    _towers.erase(tower);
}


void Grid::setDirection(Direction dir) {
    _direction = dir;
}

Grid::Direction Grid::getDirection() const {
    return _direction;
}

bool Grid::isOccupied() const {
    return _is_occupied;
}
