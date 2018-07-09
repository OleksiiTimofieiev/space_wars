/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 21:16:05 by otimofie          #+#    #+#             */
/*   Updated: 2018/06/24 09:11:49 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Space_object.hpp"
#include "Bullet.hpp"
#include "ncurses.h"
#include <iostream>
#include "Enemy.hpp"

class Player : public Space_object
{

private:
	int _HP;
	int _lives;
	int _killed;
	int _activation;
	int _supershot;
	int _time_to_next_supershot;
	std::string _name;
    std::string _figure;
	std::string _replace;

	Bullet *_bullet;

public:
	Player();
	Player( int HP, std::string name );
	~Player();	

	Player( Player const &src );
	Player & operator=( Player const &rhs );
	void	display ( WINDOW * var );
	int		getMove ( WINDOW * var );
	void	moveUp( WINDOW * var );
	void	moveDown( WINDOW * var);
	void	moveLeft( WINDOW * var);
	void	moveRight( WINDOW * var);
	void	bulletActivate( void );
	void	playerBulletMoveAndDisplay ( WINDOW * var );
	void	bulletSuperActivate( void );
	void	killEnemies (WINDOW * win, Enemy * var);
	void	killPlayer(Enemy * var, WINDOW *window);
	void	zjmp (WINDOW * win);
	int		getHP();
	int		getLives();
	int		getKilled();
    void    decrementLife();
	int 	getSupershots();
	int 	getTimeSuppershot();
	void	incrementTimeSupershot();
	void 	decrementHP();
	Bullet	*getBullets();
};




































#endif