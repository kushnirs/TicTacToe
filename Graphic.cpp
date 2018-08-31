/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graphic.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 18:59:14 by skushnir          #+#    #+#             */
/*   Updated: 2018/08/31 19:56:39 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Graphic.hpp"

Graphic::Graphic() : _name("default"), win(NULL), surface(NULL), x(0), y(0) {  }

Graphic::Graphic(std::string name, int x_, int y_) : _name(name), win(NULL), surface(NULL), x(x_), y(y_) {  }

Graphic::Graphic(Graphic const & obj) { *this = obj; }

Graphic::~Graphic() {  }

SDL_Window	* Graphic::getWin() { return (win); }

Graphic & Graphic::operator = (Graphic const & obj) { _name = obj._name; win = obj.win;
	surface = obj.surface; x = obj.x; y = obj.y; return (*this); }

void	Graphic::draw_button(int x, int y, int width, int high, int color)
{
	for (int i = y + high; i > y; i--)
		draw_line((int[2]){x, x + width - 1},(int[2]){i, i}, color);
}


void	Graphic::draw_line(int a[2], int b[2], int color)
{
	unsigned *pixels = static_cast<unsigned*>(surface->pixels);

	float x_ = a[1] - a[0];
	float y_ = b[1] - b[0];
	float length = sqrt( x_*x_ + y_*y_ );

	float addx = x_ / length;
	float addy = y_ / length;

	x_ = a[0];
	y_ = b[0];

	for(float i = 0; i < length; i += 1)
	{
		pixels[static_cast<int>(y_ * x + x_)] = color;
 		x_ += addx;
  		y_ += addy;
	}
}

void Graphic::display_message(std::string const & module, int x, int y, int font, SDL_Color color)
{
	TTF_Font				*ttf;
	SDL_Rect				dstrect;
	SDL_Surface				*param;

	ttf = TTF_OpenFont("ARIAL.TTF", font);
	if (!ttf)
		return;
	param = TTF_RenderText_Blended(ttf, module.c_str(), color);
	dstrect.x = x; dstrect.y = y;  dstrect.h = 0; dstrect.w = 0;
	SDL_BlitSurface(param, NULL, surface, &dstrect);
	TTF_CloseFont(ttf);
	SDL_FreeSurface(param);
}

void	Graphic::display_module()
{
	unsigned *pixels = static_cast<unsigned*>(surface->pixels);
	for (int i = 0; i < (surface->h * surface->w); i++)
			pixels[i] = 0xe6e6e6;
}

void	Graphic::init_module()
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	win = SDL_CreateWindow(_name.c_str(),
		SDL_WINDOWPOS_CENTERED, y, x, y, 0);
	if (!win)
	{
		std::cout << "Window error: %s\n" << std::endl;
		exit(-1);
	}
	surface = SDL_GetWindowSurface(win);
}
