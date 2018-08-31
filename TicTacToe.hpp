/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TicTacToe.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 22:33:54 by sergee            #+#    #+#             */
/*   Updated: 2018/08/31 18:48:37 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TICTACTOE_HPP
# define TICTACTOE_HPP

#include <iostream>
#include <vector>
#include "Graphic.hpp"
#include "SDL_ttf.h"
#include "SDL.h"

class TicTacToe {
private:
	Graphic disp;
	int		x;
	int		y;
	int		sector;
	int		sector_pos[2];
	int		multiplayer;
	bool	player;
	int	winner;
	std::vector<int> data;
public:
	TicTacToe();
	TicTacToe(TicTacToe const & obj);
	~TicTacToe();
	TicTacToe & operator = (TicTacToe const & obj);

	void new_game();
	void check_winner();
	void check_player_move(SDL_Event	*event);
	void check_sector(int x, int y);
	void check_press(SDL_Event	*event);
	void event_func(SDL_Event	*event);

	int		protect_func();
	int		rand_func();
	void	computer_player();
};

#endif