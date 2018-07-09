/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 21:15:40 by otimofie          #+#    #+#             */
/*   Updated: 2018/06/24 17:17:08 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Space_object.hpp"
#include "Player.hpp"
#include <ncurses.h>
#include <unistd.h>
#include "Board.hpp"
#include "constants.hpp"


int		main( void )
{
	system("afplay -v 0.5 ./sounds/Star_War.mp3 &");
	Board   *board;
    bool    lose;

    board = new Board();
    lose = board->startGame();
    delete(board);
    if (lose)
        std::cout << "You're looser" << std::endl;
    else
        std::cout << "You're winner" << std::endl;
	system("killall afplay");
	return (0);
}