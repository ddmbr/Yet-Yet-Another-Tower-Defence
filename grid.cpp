#include "grid.h"

Grid::Grid() {
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
    _tower = tower;
}

void Grid::removeTower() {
    _tower = NULL;
}


void Grid::setDirection(Direction dir) {
    _direction = dir;
}

Grid::Direction Grid::getDirection() const {
    return _direction;
}

bool Grid::isOccupied() const {
    return _tower != NULL;
}
