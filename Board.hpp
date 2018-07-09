//
// Created by Denys Burtnjak on 6/23/18.
//

#ifndef RUSH_BOARD_HPP
#define RUSH_BOARD_HPP

#include <ncurses.h>
#include <iostream>
#include "Window.hpp"
#include "Player.hpp"
#include "Asteroid.hpp"
#include <zconf.h>

class Board {

private:
    Window      *_space;
    Window      *_info;
    Window      *_instruction;
    Player      *_player;
    Enemy       *_enemies;
    Asteroid    *_asteroids;

    void    _init(void);
    void    _refreshAll();
    void    _moveAllEnemies(WINDOW *window, unsigned long frame);
    void    _displayInfoText(WINDOW *window, unsigned long frame);
    void    _moveAndDisplayAsteroids(WINDOW *window, unsigned long frame);
    void    _dispalyUsage(WINDOW *window);
    bool _startBoss();

public:
    Board();
    ~Board();
    Board(Board const & obj);
    Enemy *getEnemy( void );

    Board &operator=(Board const & obj);

    bool startGame();
};


#endif //RUSH_BOARD_HPP
