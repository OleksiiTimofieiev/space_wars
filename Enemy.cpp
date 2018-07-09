
#include "Enemy.hpp"

int     Enemy::getEnemyX( void ) {return _coord_x;};
int     Enemy::getEnemyY( void ) {return _coord_y;};

Enemy::~Enemy() {
    delete (this->_bullet);
}

Enemy::Enemy(const Enemy &obj) {
    *this = obj;
}

Enemy::Enemy() {
    _active = false;
    this->_boardView = "<[]>";
    this->_deleteStr = "   ";
    this->_prev_y = 0;
    this->_prev_x = 4;
    this->_bullet = new Bullet();
}

void Enemy::recreate() {
    this->_active = true;
    srand(clock());
    this->_coord_x = 140;
    this->_coord_y = rand() % 45;

    _bullet->setActivation();
    int y = _coord_y;
    int x = _coord_x;
    _bullet->setCoords( _coord_y, x-= 5);
}

void Enemy::_putAllBulletsOnWindow(WINDOW *window) 
{
    _bullet->move("left");

    if (_bullet->getActivation() == 1)
    {
        _bullet->display(window, "left");
    }
}

void Enemy::move(WINDOW *window) {
    static int moves = 0;

    if (_coord_x > 0)
    {
        (_coord_x)--;
        moves++;
        if (moves == 40)
        {
            mvwprintw(window, _coord_y, _coord_x, "%s", "     ");
            (_coord_y)+= 2;
        }
        else if (moves == 80)
        {
            mvwprintw(window, _coord_y, _coord_x, "%s", "     ");
            (_coord_y)-= 4;
            moves = 0;
        }
    }
    else
        _active = false;
}

void Enemy::putEnemyAndBullets(WINDOW *window) {
    if (_active == true)
        putOnWindow(window);
    else
    {
        mvwprintw(window, _coord_y, _coord_x, "%s", "    ");
        wrefresh(window);
    }
    _putAllBulletsOnWindow(window);
}

bool Enemy::isActive() {
    return _active;
}

void    Enemy::setActiveFalse( void )
{
    _active = false;
}

void    Enemy::deactivate (WINDOW *window)
{
    _active = false;
    mvwprintw(window, _coord_y, _coord_x, "%s", "      ");
}

Bullet *Enemy::getBullet() {
    return _bullet;
}

Enemy &Enemy::operator=(Enemy const &obj) {
    if (this == &obj)
        return *this;
    this->_coord_y = obj._coord_y;
    this->_coord_y = obj._coord_x;
    this->_prev_y = obj._prev_y;
    this->_prev_x = obj._prev_x;
    this->_bullet = obj._bullet;
    return *this;
}
