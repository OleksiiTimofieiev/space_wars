//
// Created by Denys Burtnjak on 6/24/18.
//

#ifndef RUSH_BOSS_HPP
#define RUSH_BOSS_HPP


#include "Space_object.hpp"
#include "Player.hpp"

class Boss : public Space_object{
private:
    Bullet  *_bullets;
    bool    _active;

public:
    Boss();
    ~Boss();
    Boss(Boss const & obj);

    Boss    &operator=(Boss const &obj);

    void    move(Player *player);
    void    display(WINDOW *window);
    void    setAndActivateBullets();
    void    moveBulletsAndDisplay(WINDOW *window);
    Bullet  *getBullets();
    void    killPlayer(Player *player);
    bool    isActive();
    void    snoopDogg(Player *player);
};


#endif //RUSH_BOSS_HPP
