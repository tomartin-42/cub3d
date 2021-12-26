/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommy <tommy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 19:48:57 by tommy             #+#    #+#             */
/*   Updated: 2021/12/25 20:07:48 by tommy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paint.h"

void	get_texture_addr(t_win *win)
{
	win->text[0].addr = mlx_get_data_addr(win->text[0].img,
			&win->text[0].bits_per_pixel, &win->text[0].line_length,
			&win->text[0].endian);
	win->text[1].addr = mlx_get_data_addr(win->text[1].img,
			&win->text[1].bits_per_pixel, &win->text[1].line_length,
			&win->text[1].endian);
	win->text[2].addr = mlx_get_data_addr(win->text[2].img,
			&win->text[2].bits_per_pixel, &win->text[2].line_length,
			&win->text[2].endian);
	win->text[3].addr = mlx_get_data_addr(win->text[3].img,
			&win->text[3].bits_per_pixel, &win->text[3].line_length,
			&win->text[3].endian);
}

void	get_textures(t_win *win, t_map *mapi)
{
	win->text[0].img = mlx_xpm_file_to_image(win->mlx, mapi->NO_rute,
			&(win->text[0].width), &(win->text[0].height));
	win->text[1].img = mlx_xpm_file_to_image(win->mlx, mapi->EA_rute,
			&(win->text[1].width), &(win->text[1].height));
	win->text[2].img = mlx_xpm_file_to_image(win->mlx, mapi->SO_rute,
			&(win->text[2].width), &(win->text[2].height));
	win->text[3].img = mlx_xpm_file_to_image(win->mlx, mapi->WE_rute,
			&(win->text[3].width), &(win->text[3].height));
	get_texture_addr(win);
}