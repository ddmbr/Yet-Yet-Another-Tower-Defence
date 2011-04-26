#include "tower.h"

Tower::Tower() {
}

Tower::~Tower() {
}

void Tower::setCoord(int x, int y) {
    _x = x;
    _y = y;
}

void Tower::setCooldown(int cooldown) {
    _cooldown = cooldown;
}


int Tower::getX() {
    return _x;
}

int Tower::getY() {
    return _y;
}
