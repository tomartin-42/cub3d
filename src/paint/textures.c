/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 19:48:57 by tommy             #+#    #+#             */
/*   Updated: 2022/01/15 14:16:51 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paint.h"
#include "check.h"

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

void	get_textures(t_win *win, t_map *mapi, char **map)
{
	win->text[0].img = mlx_xpm_file_to_image(win->mlx, mapi->no_route,
			&(win->text[0].width), &(win->text[0].height));
	win->text[1].img = mlx_xpm_file_to_image(win->mlx, mapi->we_route,
			&(win->text[1].width), &(win->text[1].height));
	win->text[2].img = mlx_xpm_file_to_image(win->mlx, mapi->so_route,
			&(win->text[2].width), &(win->text[2].height));
	win->text[3].img = mlx_xpm_file_to_image(win->mlx, mapi->ea_route,
			&(win->text[3].width), &(win->text[3].height));
	if (!win->text[0].img || !win->text[1].img
		|| !win->text[2].img || !win->text[3].img)
		error_read_texture(mapi, map);
	get_texture_addr(win);
}

//Calculate texture wall
int	calculate_wall_texture(t_ray *ray, int x)
{
	int	text_type;

	if (ray[x].side == 0 && ray[x].ray_d_x < 0)
		text_type = N_W;
	if (ray[x].side == 0 && ray[x].ray_d_x >= 0)
		text_type = E_W;
	if (ray[x].side == 1 && ray[x].ray_d_y < 0)
		text_type = S_W;
	if (ray[x].side == 1 && ray[x].ray_d_y >= 0)
		text_type = W_W;
	return (text_type);
}
