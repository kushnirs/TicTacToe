/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TicTacToe.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 22:33:40 by sergee            #+#    #+#             */
/*   Updated: 2018/08/31 18:24:12 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "TicTacToe.hpp"

TicTacToe::TicTacToe() : x(300), y(300), sector(0), multiplayer(0), player(false), winner(0) {
	data = std::vector<int> (9);
	disp = Graphic ("TicTacToe", x, y + 45);
	disp.init_module();
	
	SDL_Event		event;

	srand(time(0));
	new_game();
	while (1)
	{
		while (SDL_PollEvent(&event))
			event_func(&event);
		if (multiplayer == 1 && player)
			computer_player();
		check_winner();
		if (winner)
			winner == 1 ? disp.display_message("Player 1(o) win", 80, 165, 30)
				: disp.display_message("Player 2(x) win", 80, 165, 30);
		SDL_UpdateWindowSurface(disp.getWin());
	}
}

TicTacToe::TicTacToe(TicTacToe const & obj) { *this = obj; }

TicTacToe::~TicTacToe() {  }

TicTacToe & TicTacToe::operator = (TicTacToe const & obj) { data = obj.data; return (*this); }

// 0 1 2
// 3 4 5
// 6 7 8

void	TicTacToe::check_winner()
{
	data[0] && data[0] == data[1] && data[1] == data[2] ? winner = data[0] : 0;
	data[3] && data[3] == data[4] && data[4] == data[5] ? winner = data[3] : 0;
	data[6] && data[6] == data[7] && data[7] == data[8] ? winner = data[6] : 0;
	data[0] && data[0] == data[3] && data[3] == data[6] ? winner = data[0] : 0;
	data[1] && data[1] == data[4] && data[4] == data[7] ? winner = data[1] : 0;
	data[2] && data[2] == data[5] && data[5] == data[8] ? winner = data[2] : 0;
	data[0] && data[0] == data[4] && data[4] == data[8] ? winner = data[0] : 0;
	data[2] && data[2] == data[4] && data[4] == data[6] ? winner = data[2] : 0;
}

void TicTacToe::computer_player()
{
	player = false;
	int	arr[9][2] = {{0,0},{100,0},{200,0},
					{0,100},{100,100},{200,100},
					{0,200},{100,200},{200,200}
				};
	if (!data[4])
	{
		disp.display_message("x", arr[4][0] + 30, arr[4][1] + 45, 80);
		data[4] = 2;
	}
	else if (data[4] == 2)
	{
		for (int i = 0; i < 9; i += 2)
		{
			if (!data[i])
			{
				data[i] = 2;
				disp.display_message("x", arr[i][0] + 30, arr[i][1] + 45, 80);
				return;
			}
		}
	}
	else
	{
		std::vector<int> tmp;
		for (int i = 0; i < 9; i++)
			if (!data[i])
				tmp.push_back(i);
		if (!tmp.empty())
		{
			printf("lox\n");
			int i = rand() % tmp.size();
			data[tmp[i]] = 2;
			disp.display_message("x", arr[tmp[i]][0] + 30, arr[tmp[i]][1] + 45, 80);
			return;
		}
	}

}

void TicTacToe::new_game()
{
	data = std::vector<int> (9);
	multiplayer = 0;
	player = false;
	winner = 0;
	disp.display_module();
	disp.draw_line((int[2]){0, x - 1 }, (int[2]){y / 3 + 45, y / 3 + 45}, 0);
	disp.draw_line((int[2]){0, x}, (int[2]){y / 3 * 2 + 45, y / 3 * 2 + 45}, 0);
	disp.draw_line((int[2]){x / 3, x / 3}, (int[2]){45, y + 45}, 0);
	disp.draw_line((int[2]){x * 0.66, x * 0.66}, (int[2]){45, y + 45}, 0);
	disp.draw_line((int[2]){0, x}, (int[2]){45,45}, 0);
	disp.draw_button(40, 10, 100, 30, 0x079AB7);
	disp.display_message("singleplayer", 47, 15, 17);
	disp.draw_button(160, 10, 100, 30, 0x079AB7);
	disp.display_message("multiplayer", 170, 15, 17);
}

void TicTacToe::check_sector(int x_, int y_)
{
	int h = 0, w = 0;

	y_ > 45 && y_ <= y / 3 + 45 ? h = 0 : 0;
	y_ > y / 3 + 45 && y_ <= y * 0.66 + 45 ? h = 1 : 0;
	y_ > y * 0.66 + 45 && y_ < y + 45 ? h = 2 : 0;

	x_ <= 100 ? w = 0 : 0;
	x_ > 100 && x_ < 200 ? w = 1 : 0;
	x_ >= 200 ? w = 2 : 0;

	sector = w + h * 3;
	sector_pos[0] = w * 100;
	sector_pos[1] = h * 100 + 45;
}

void TicTacToe::check_player_move(SDL_Event	*event)
{
	check_sector(event->button.x, event->button.y);
	if (data[sector] || !multiplayer)
		return;
	if (!player)
		disp.display_message("o", sector_pos[0] + 27, sector_pos[1], 80);
	else
		if (multiplayer == 2)
			disp.display_message("x", sector_pos[0] + 30, sector_pos[1], 80);
	data[sector] = !player ? 1 : 2;
	player = !player ? true : false;
}

void TicTacToe::check_press(SDL_Event	*event)
{
	for (int i = 0; i < 9; i++)
	{
		if (!(i % 3))
			printf("\n");
		printf("%d ", data[i]);
	}
	printf("\n");
	// if (winner)
	// 	return new_game();
	 if (event->button.x >= 40 && event->button.x <= 140 && event->button.y >= 10 && event->button.y <= 40)
	{
	 	disp.draw_button(40, 10, 100, 30, 0x056375);
		SDL_UpdateWindowSurface(disp.getWin());
		usleep(20000);
	 	new_game();
	 	multiplayer = 1;
	}
	else if (event->button.x >= 160 && event->button.x <= 260 && event->button.y >= 10 && event->button.y <= 40)
	{
		disp.draw_button(160, 10, 100, 30, 0x056375);
		SDL_UpdateWindowSurface(disp.getWin());
		usleep(20000);
	 	new_game();
	 	multiplayer = 2;
	}
	else if (event->button.y >= 45)
		check_player_move(event);
}

void TicTacToe::event_func(SDL_Event	*event)
{
	if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.sym == SDLK_ESCAPE)
			exit(0);
	}
	else if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		if (event->button.button == SDL_BUTTON_LEFT)
			check_press(event); 
	}
	else if (event->type == SDL_QUIT)
	{
		exit(0);
	}
}