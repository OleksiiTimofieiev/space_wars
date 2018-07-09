/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bullet.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 21:15:53 by otimofie          #+#    #+#             */
/*   Updated: 2018/06/24 10:55:01 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BULLET_HPP
#define BULLET_HPP

#include <ncurses.h>
#include <iostream>

class Bullet
{
private:
	bool _activation;
	int  _b_coord_x;
	int  _b_coord_y;

public:
	Bullet();
	~Bullet();
	Bullet(Bullet const &obj);

	Bullet &operator=(Bullet const & obj);

	bool	getActivation( void );

	void	setActivation( void );
	void	setCoords( int coordX, int coordY );

	void	move( std::string direction );
	void	display( WINDOW * var, std::string direction );

	int		getBulletX( void );
	int		getBulletY( void );

};

#endif
