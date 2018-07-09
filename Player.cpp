/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 21:16:08 by otimofie          #+#    #+#             */
/*   Updated: 2018/06/24 16:50:34 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"
#include "Space_object.hpp"
#include "constants.hpp"

Player::Player() {};

Player::~Player() {
    delete[](_bullet);
};

Player::Player( int HP, std::string name ) : Space_object(23, 1) 
{
	this->_lives = PLAYER_LIVES;
	this->_HP = HP;
	this->_name = name;
    this->_supershot = 0;
    this->_time_to_next_supershot = 0;
	this->_activation = 0;
	this->_bullet = new Bullet[BULLETS_QUANTITY];

    this->_figure = "/.>.\\";
    this->_replace = "      ";
};

Player::Player( Player const &src )
{
	*this = src;
}

Player & Player::operator=( Player const &obj )
{
	if (this != &obj)
	{
        _HP = obj._HP;
        _lives = obj._lives;
        _killed = obj._killed;
        _activation = obj._activation;
        _supershot = obj._supershot;
        _time_to_next_supershot = obj._time_to_next_supershot;
        _coord_y = obj._coord_y;
        _coord_y = obj._coord_x;
        _prev_y = obj._prev_y;
        _prev_x = obj._prev_x;
        _bullet = obj._bullet;
        _name = obj._name;
        _figure = obj._figure;
        _replace = obj._replace;
        _bullet = obj._bullet;
	}
	return (*this);
}

void	Player::display ( WINDOW * var )
{
	start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);

	wattron(var, COLOR_PAIR(1));
	wattron(var, A_BOLD);
	mvwprintw(var, this->_coord_x, this->_coord_y, "%s", _figure.c_str());
	wattroff(var, COLOR_PAIR(1));
}

int		Player::getMove ( WINDOW * var )
{
	int	choice = wgetch(var);

	switch (choice)
	{
		case KEY_UP:
		{
			moveUp(var);
			break; 
		}
		case KEY_DOWN:
		{
			moveDown(var);
			break; 
		}
		case KEY_LEFT:
		{
			moveLeft(var);
			break; 
		}
		case KEY_RIGHT:
		{
			moveRight(var);
			break; 
		}
		case ' ':
		{

			bulletActivate();
			break; 
		}
		case 's':
		{
			bulletSuperActivate();
			break; 
		}
		case 'j':
		{
			zjmp(var);
			break; 
		}
		default: break;
	}
	return (choice);
}

void	Player::moveUp(WINDOW * var)
{
	mvwprintw(var, this->_coord_x, this->_coord_y, "%s", _replace.c_str());
	this->_coord_x--;
	if (this->_coord_x == 0)
		this->_coord_x = 1;
}

void	Player::moveDown(WINDOW * var)
{
	mvwprintw(var, this->_coord_x, this->_coord_y, "%s", _replace.c_str());
	this->_coord_x++;
	if (this->_coord_x == WINDOW_H - 2)
		this->_coord_x = WINDOW_H - 3;
}

void	Player::moveLeft(WINDOW * var)
{
	mvwprintw(var, this->_coord_x, this->_coord_y, "%s", _replace.c_str());
	this->_coord_y--;
	if (this->_coord_y == 0)
		this->_coord_y = 1;
}

void	Player::moveRight(WINDOW * var)
{
	mvwprintw(var, this->_coord_x, this->_coord_y, "%s", _replace.c_str());
	this->_coord_y++;
	if (this->_coord_y == WINDOW_W - 2)
		this->_coord_y = WINDOW_W - 3;
}

void	Player::bulletActivate( void )
{
	int i = 0;
	int x;
	int y;

	while (i < BULLETS_QUANTITY - 5)
	{
		if (this->_bullet[i].getActivation() == 0)
		{
			x = _coord_x;
			y = _coord_y;

			_bullet[i].setActivation();
			_bullet[i].setCoords(x, y += 5);
			system("afplay ./sounds/Laser-shot.mp3 &");
			break;
		}	
		i++;
	}
}

void	Player::bulletSuperActivate( void )
{
	if (_supershot < SUPERSHOT_QUANTITY && _time_to_next_supershot == 5)
	{
		int x;
		int y;

		x = _coord_x;
		y = _coord_y;

		_bullet[5].setActivation();
		_bullet[6].setActivation();
		_bullet[7].setActivation();
		_bullet[8].setActivation();
		_bullet[9].setActivation();

		_bullet[5].setCoords(x-= 2, y += 7);
		_bullet[6].setCoords(x+= 1, y );
		_bullet[7].setCoords(x+= 1, y );
		_bullet[8].setCoords(x+= 1, y );
		_bullet[9].setCoords(x+= 1, y );
		system("afplay -t 2 ./sounds/Heavy-machine-gun-rapid-fire-sound-effect.mp3 &");
		_supershot++;
	}
	else
		system("afplay ./sounds/Shotgun-reloading.mp3 &");
    if (_time_to_next_supershot == 5)
        _time_to_next_supershot = 0;
}

void	Player::playerBulletMoveAndDisplay ( WINDOW * var )
{
	int i = 0;

	while (i < BULLETS_QUANTITY )
	{
		if (_bullet[i].getActivation() == 1)
		{
			_bullet[i].move("right");
			_bullet[i].display(var, "right");
		}	
		i++;
	}
}

void	Player::killEnemies (WINDOW * win, Enemy *var)
{
	int bullet = 0;
	int enemy = 0;

	while (bullet < BULLETS_QUANTITY)
	{
		enemy = 0;
		while (enemy < 20)
		{
			if (var[enemy].isActive() && _bullet[bullet].getBulletX() == var[enemy].getEnemyY() &&
                    _bullet[bullet].getBulletY() == var[enemy].getEnemyX())
			{
				var[enemy].setActiveFalse();
                _killed++;
			}
			enemy++;
		}
		bullet++;
	}	
}

void	Player::zjmp (WINDOW * win)
{
	mvwprintw(win, this->_coord_x, this->_coord_y, "%s", _replace.c_str());

	_coord_x += 10;
	_coord_y += 10;

	if (_coord_y >= 145)
		_coord_y = 20;
	else if (_coord_x >= 47)
		_coord_x = 15;

}

void	Player::killPlayer (Enemy *var, WINDOW *window)
{
	int     enemy = 0;
    bool    enemy_colision;
    bool    bullet_colision;

	while (enemy < 20)
	{
        if (var[enemy].isActive()) {
            for (int i = 0; i < 4; i++) {
                enemy_colision = var[enemy].getEnemyY() == _coord_x && var[enemy].getEnemyX() == _coord_y;
                bullet_colision = var[enemy].getBullet()->getBulletX() == _coord_x &&
                        var[enemy].getBullet()->getBulletY() == _coord_y;

                if (enemy_colision) {
                    this->_HP -= 20;
                    var[enemy].deactivate(window);
                    break ;
                }
				if (bullet_colision) {
					this->_HP -= 20;
				}
            }
        }
		enemy++;
	}
}

int Player::getHP() {
	return this->_HP;
}

int Player::getKilled() {
	return this->_killed;
}

int Player::getLives() {
	return this->_lives;
}

void Player::decrementLife() {
    this->_lives--;
    this->_HP = PLAYER_HP;
}

int Player::getSupershots() {
    return _supershot;
}

int Player::getTimeSuppershot() {
    return _time_to_next_supershot;
}

void Player::incrementTimeSupershot() {
    if (_time_to_next_supershot < 5 && _supershot < 5)
        this->_time_to_next_supershot++;
}

void Player::decrementHP() {
	_HP -= 20;
}

Bullet	*Player::getBullets(){
	return (this->_bullet);
}
