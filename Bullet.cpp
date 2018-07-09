/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bullet.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 21:15:48 by otimofie          #+#    #+#             */
/*   Updated: 2018/06/24 13:30:49 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bullet.hpp"

	int 	Bullet::getBulletX( void ) {return _b_coord_x;};
	int 	Bullet::getBulletY( void ) {return _b_coord_y;};


	Bullet::Bullet( void )
	{
		this->_activation = 0;
		this->_b_coord_x = 0;
		this->_b_coord_y = 0;
	};
	
	Bullet::~Bullet() {};

	bool	Bullet::getActivation( void ) {return _activation;};

	void	Bullet::setActivation( void ) {_activation = 1;};
	void	Bullet::setCoords( int coordX, int coordY ) { _b_coord_x = coordX; _b_coord_y = coordY;};
	
	void	Bullet::move( std::string direction )
	{
		if (direction == "right")
		{
			if (_b_coord_y < 149 && _activation == 1)
				_b_coord_y++;
			else
			{
				_activation = 0;
				_b_coord_x = 0;
				_b_coord_y = 0;
			}
		}
		else
		{
			if (_b_coord_y >= 0 && _activation == 1)
				_b_coord_y--;
			else
			{
				_activation = 0;
			}
		}
	}

	void	Bullet::display( WINDOW * var, std::string direction )
	{

		start_color();
		if (direction == "right")
		{
			init_pair(2, COLOR_GREEN, COLOR_BLACK);
			wattron(var, A_BOLD);
			wattron(var, COLOR_PAIR(2));
			mvwprintw(var, _b_coord_x, _b_coord_y, ">");
			wattroff(var, COLOR_PAIR(1));
			mvwprintw(var, _b_coord_x, _b_coord_y - 1, " ");
		}
		else
		{
			init_pair(2, COLOR_GREEN, COLOR_BLACK);
			wattron(var, A_BOLD);
			wattron(var, COLOR_PAIR(2));
			mvwprintw(var, _b_coord_x, _b_coord_y + 1, " ");
			wattroff(var, COLOR_PAIR(1));
			mvwprintw(var, _b_coord_x, _b_coord_y, "<");
		}

	}

Bullet::Bullet(Bullet const &obj) {
	*this = obj;
}

Bullet &Bullet::operator=(Bullet const &obj) {
	if (this == &obj)
		return (*this);
	_activation = obj._activation;
	_b_coord_x = obj._b_coord_x;
	_b_coord_y = obj._b_coord_y;
	return (*this);
}


