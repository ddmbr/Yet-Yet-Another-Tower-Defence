#include "grid.h"

Grid::Grid()
    :_is_walkable(true) {
}

Grid::~Grid() {

}

void Grid::setWalkable(bool walkable) {
    _is_walkable = walkable;
}

void Grid::setDirection(Direction dir) {
    _direction = dir;
}

Grid::Direction Grid::getDirection() const {
    return _direction;
}

bool Grid::isWalkable() const {
    return _is_walkable;
}
