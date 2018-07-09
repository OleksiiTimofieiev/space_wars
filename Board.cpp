//
// Created by Denys Burtnjak on 6/23/18.
//

#include "Board.hpp"
#include "constants.hpp"
#include "Boss.hpp"

Enemy *Board::getEnemy( void ) {return _enemies;}

void Board::_init(void) {
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    start_color();
    raw();
    _player = new Player(100, "Destroyer");
    _space = new Window(WINDOW_W, WINDOW_H, 0, 0);
    _info = new Window(50, 25, WINDOW_W - 2, 0);
    _instruction = new Window(50, 25, WINDOW_W - 2, 25);
    _enemies = new Enemy[20];
    _asteroids = new Asteroid[50];
    keypad(_space->getWindow(), true);
    nodelay(_space->getWindow(), true);
    refresh();
}

Board::Board()
{
    this->_init();
}

Board::~Board() {
    delete(_player);
    delete(_space);
    delete(_info);
    delete(_instruction);
    delete[](_enemies);
    delete[](_asteroids);
    curs_set(TRUE);
    endwin();
}

Board::Board(Board const &obj) {
    *this = obj;
}

Board &Board::operator=(Board const &obj) {
    if (this == &obj)
        return *this;
    _space = obj._space;
    _info = obj._info;
    _instruction = obj._instruction;
    _player = obj._player;
    _enemies = obj._enemies;
    _asteroids = obj._asteroids;
    return *this;
}

bool Board::startGame() {
    unsigned long   frame;
    bool            lose;

    frame = 0;
    _dispalyUsage(_instruction->getWindow());
    do
    {
        if (_player->getHP() <= 0)
            _player->decrementLife();

        if (_player->getLives() <= 0) {
            lose = true;
            break;
        }

        if (_player->getKilled() >= 30) {
            lose = false;
            break;
        }

        this->_moveAndDisplayAsteroids(_space->getWindow(), frame);

        _moveAllEnemies(_space->getWindow(), frame);
        
        _player->killPlayer(_enemies, _space->getWindow());

        _player->killEnemies(_space->getWindow(), _enemies);

        if (frame % 10 == 0)
            _displayInfoText(_info->getWindow(), frame);

        if (frame % 100 == 0)
            _player->incrementTimeSupershot();

        _player->playerBulletMoveAndDisplay(_space->getWindow());

        _player->display(_space->getWindow());


        _refreshAll();
        frame++;
        usleep(10000);
    }
    while(_player->getMove(_space->getWindow()) != 27);

    if (!lose)
        return _startBoss();
    return lose;
}

void Board::_refreshAll() {
    this->_space->refreshAll();
    this->_info->refreshAll();
    this->_instruction->refreshAll();
}

void Board::_moveAllEnemies(WINDOW *window, unsigned long frame) 
{
    bool    makeActive;

    makeActive = true;
    for (int i = 0; i < 20; i++) {
        if (!_enemies[i].isActive() && makeActive && frame % 100 == 0) {
            makeActive = false;
            this->_enemies[i].recreate();
        }
        this->_enemies[i].putEnemyAndBullets(window);
        if (_enemies[i].isActive() && frame % 10 == 0) {
            this->_enemies[i].move(window);
        }
    }
}

void Board::_displayInfoText(WINDOW *window, unsigned long frame) {
    wclear(window);
    wprintw(window, "\n  %-35s%d.%d s\n\n", "Play time:", frame / 100, (frame % 100) / 10);
    wprintw(window, "  %-35s%d\n\n", "Lives:", this->_player->getLives());
    wprintw(window, "  %-35s%d\n\n", "HP:", this->_player->getHP());
    wprintw(window, "  %-35s%d\n\n", "Score:", this->_player->getKilled());
    wprintw(window, "  %-35s%d / %d\n\n", "Supershots:", this->_player->getSupershots(), SUPERSHOT_QUANTITY);
    wprintw(window, "  %-35s%d / %d\n\n", "Reloade time:", this->_player->getTimeSuppershot(), 5);
}

void Board::_moveAndDisplayAsteroids(WINDOW *window, unsigned long frame) {
//    if (frame % 10)
//        return;
    for (int i = 0; i < 50; i++) {
        _asteroids[i].move();
        _asteroids[i].putOnWindow(window);
    }
}

void Board::_dispalyUsage(WINDOW *window) {
    wprintw(window, "\n     %-20s %s\n\n", "QUIT", "esc");
    wprintw(window, "     %-20s %s\n\n", "UP", "key up");
    wprintw(window, "     %-20s %s\n\n", "DOWN", "key down");
    wprintw(window, "     %-20s %s\n\n", "LEFT", "key left");
    wprintw(window, "     %-20s %s\n\n", "RIGHT", "key right");
    wprintw(window, "     %-20s %s\n\n", "SHOT", "space");
    wprintw(window, "     %-20s %s\n\n", "SUPER SHOT", "'s'");
    wprintw(window, "     %-20s %s\n\n", "TELEPORT", "'j'");
    init_pair(200, COLOR_RED, COLOR_BLACK);
    wattron(window, COLOR_PAIR(200));
    wprintw(window, "\n   powered by: otimofie, dburtnja\n");
    wprintw(window, "\tall rights reserved");
    wattroff(window, COLOR_PAIR(200));
    wrefresh(window);
}

bool Board::_startBoss() {
    unsigned long   frame;
    Boss            _boss;

    frame = 0;
    _boss.setAndActivateBullets();
    system("afplay ./sounds/Clucking-chicken.mp3 &");
    do
    {
        if (_player->getHP() <= 0)
            _player->decrementLife();

        if (_player->getLives() <= 0)
            return true;

        if (!_boss.isActive())
            return true;

        this->_moveAndDisplayAsteroids(_space->getWindow(), frame);

        _moveAllEnemies(_space->getWindow(), frame);

        _player->killPlayer(_enemies, _space->getWindow());

        _player->killEnemies(_space->getWindow(), _enemies);

        if (frame % 10 == 0)
            _displayInfoText(_info->getWindow(), frame);

        if (!_boss.getBullets()[0].getActivation())
            _boss.setAndActivateBullets();

        if (frame % 10 == 0) {
            _player->incrementTimeSupershot();
            _boss.move(_player);
        }
        _boss.moveBulletsAndDisplay(_space->getWindow());
        _boss.display(_space->getWindow());
        _boss.killPlayer(_player);

        _player->playerBulletMoveAndDisplay(_space->getWindow());

        _player->display(_space->getWindow());


        _refreshAll();
        frame++;
        usleep(10000);
    }
    while(_player->getMove(_space->getWindow()) != 27);
    return true;
}
