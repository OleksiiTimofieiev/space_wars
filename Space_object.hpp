/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Space_object.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 10:19:45 by otimofie          #+#    #+#             */
/*   Updated: 2018/06/23 15:51:33 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPACE_OBJECT_HPP
#define SPACE_OBJECT_HPP

#include <iostream>
#include <ncurses.h>

class Space_object
{

protected:
	int	_coord_x;
	int _coord_y;
	int _prev_x;
	int _prev_y;
	std::string	_boardView;
	std::string	_deleteStr;
	
public:
	Space_object();
	Space_object( int coord_x, int coord_y );

	~Space_object();

	Space_object( Space_object const &src );
	Space_object & operator = ( Space_object const &src );

	void	putOnWindow(WINDOW *window);
	int		getX();
	int 	getY();
};

#endif