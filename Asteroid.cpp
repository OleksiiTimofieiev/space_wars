//
// Created by Denys Burtnjak on 6/24/18.
//

#include "Asteroid.hpp"

Asteroid::Asteroid() {
    this->_boardView = ".";
    this->_deleteStr = " ";
    this->_prev_y = 0;
    this->_prev_x = 1;
    srand(clock());
    this->_coord_x = rand() % 140;
    this->_coord_y = rand() % 45; //TODO try max min;
}

Asteroid::~Asteroid() {

}

Asteroid::Asteroid(Asteroid const &obj) {
    *this = obj;
}

void Asteroid::recreate() {
    srand(clock());
    this->_coord_x = 140;
    this->_coord_y = rand() % 45; //TODO try max min;
}

void Asteroid::move() {
    if (this->_coord_x >= WINDOW_W || this->_coord_x <= -1 || this->_coord_y >= WINDOW_H || this->_coord_y <= 0)
        this->recreate();
    _coord_x--;
}

Asteroid &Asteroid::operator=(Asteroid const &obj) {
    if (this == &obj)
        return *this;
    this->_coord_y = obj._coord_y;
    this->_coord_y = obj._coord_x;
    this->_prev_y = obj._prev_y;
    this->_prev_x = obj._prev_x;
    this->_active = obj._active;
    return *this;
}
