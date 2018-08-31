/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graphic.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 18:59:16 by skushnir          #+#    #+#             */
/*   Updated: 2018/08/31 19:56:26 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_HPP
# define GRAPHIC_HPP

#include <iostream>
#include "SDL_ttf.h"
#include "SDL.h"

class Graphic {
private:
	std::string			_name;
	SDL_Window			*win;
	SDL_Surface			*surface;
	int					x;
	int					y;
public:
	Graphic();
	Graphic(std::string name, int x, int y);
	Graphic(Graphic const & obj);
	~Graphic();
	SDL_Window	*getWin();
	void	init_module();
	void 	display_message(std::string const & module, int x, int y, int font, SDL_Color color);
	Graphic & operator = (Graphic const & obj);

	void	display_module();
	void	draw_line(int x[2], int y[2], int color);
	void	draw_button(int x, int y, int width, int high, int color);
};

#endif