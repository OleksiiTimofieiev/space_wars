/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Space_object.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 10:19:41 by otimofie          #+#    #+#             */
/*   Updated: 2018/06/24 01:13:43 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Space_object.hpp"

Space_object::Space_object() {};

Space_object::~Space_object() {};

Space_object::Space_object( int coord_x, int coord_y ) : _coord_x(coord_x), _coord_y(coord_y) {};

Space_object::Space_object( Space_object const &src )
{
	*this = src;
}

Space_object & Space_object::operator=( Space_object const &rhs )
{
	if (this != &rhs)
	{
		_coord_x = rhs._coord_x;
		_coord_y = rhs._coord_y;
		_prev_x = rhs._prev_x;
		_prev_y = rhs._prev_y;
		_boardView = rhs._boardView;
		_deleteStr = rhs._deleteStr;
	}
	return (*this);
}

void Space_object::putOnWindow(WINDOW *window) {
    mvwprintw(window, this->_coord_y + this->_prev_y, this->_coord_x + this->_prev_x, this->_deleteStr.c_str());
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
	wattron(window, A_BOLD);
	wattron(window, COLOR_PAIR(3));
	mvwprintw(window, this->_coord_y, this->_coord_x, this->_boardView.c_str());
	wattroff(window, COLOR_PAIR(3));
}

int Space_object::getX() {
    return this->_coord_x;
}

int Space_object::getY() {
    return this->_coord_y;
}


