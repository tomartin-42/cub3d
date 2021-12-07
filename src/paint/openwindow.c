/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openwindow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:39:38 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/06 17:28:08 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paint.h"

static t_player	*init_player(t_map *mapi)
{
	t_player	*player;

	player = malloc (sizeof(t_player));
	player->p_player.x = (mapi->xy_init_point[0]);
	player->p_player.y = (mapi->xy_init_point[1]);
	if (mapi->init_point == 'N')
		load_values_v(&player->dir_player, 0, -1);
	else if (mapi->init_point == 'S')
		load_values_v(&player->dir_player, 0, 1);
	else if (mapi->init_point == 'E')
		load_values_v(&player->dir_player, 1, 0);
	else if (mapi->init_point == 'W')
		load_values_v(&player->dir_player, -1, 0);
	load_values_v(&player->camera, 0, 0.66);
	return (player);
}

void	init_window(t_map *mapi, char *argv)
{
	t_win		win;
	t_data		img;
	t_player	*player;

	win.mlx = mlx_init();
	(void)mapi;
	win.mlx_win = mlx_new_window(win.mlx, SCR_W, SCR_H, argv);
	img.img = mlx_new_image(win.mlx, SCR_W, SCR_H);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	player = init_player(mapi);
	print_player(player);
	mlx_loop(win.mlx);
}
