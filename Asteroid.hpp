//
// Created by Denys Burtnjak on 6/24/18.
//

#ifndef RUSH_ASTEROID_HPP
#define RUSH_ASTEROID_HPP

#include "Space_object.hpp"
#include "constants.hpp"

class Asteroid : public Space_object {
private:
    bool    _active;

public:
    Asteroid();
    ~Asteroid();
    Asteroid(Asteroid const & obj);

    Asteroid &operator=(Asteroid const &obj);
    void    recreate();
    void    move();
};


#endif //RUSH_ASTEROID_HPP
