/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openwindow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:39:38 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/08 19:17:27 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paint.h"

static int	clouse(t_win *win)
{
	mlx_destroy_window(win->mlx, win->mlx_win);
	free_mapi(win->mapi);
	exit (0);
	return (0);
}

static t_player	*init_ply(t_map *mapi)
{
	t_player	*ply;

	ply = malloc (sizeof(t_player));
	ply->p_ply.x = (mapi->xy_init_point[0]);
	ply->p_ply.y = (mapi->xy_init_point[1]);
	if (mapi->init_point == 'N')
		load_values_v(&ply->dir_ply, 0, -1);
	else if (mapi->init_point == 'S')
		load_values_v(&ply->dir_ply, 0, 1);
	else if (mapi->init_point == 'E')
		load_values_v(&ply->dir_ply, 1, 0);
	else if (mapi->init_point == 'W')
		load_values_v(&ply->dir_ply, -1, 0);
	load_values_v(&ply->camera, 0, 0.66);
	return (ply);
}

void	init_window(t_map *mapi, char *argv)
{
	t_win		win;
	t_data		img;
	t_player	*ply;

	win.mlx = mlx_init();
	win.mapi = mapi;
	win.mlx_win = mlx_new_window(win.mlx, SCR_W, SCR_H, argv);
	img.img = mlx_new_image(win.mlx, SCR_W, SCR_H);
	mlx_key_hook(win.mlx_win, key_hook, &win);
	mlx_hook(win.mlx_win, 17, 0, clouse, &win);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	ply = init_ply(mapi);
	ray_loop(ply);
	//print_player(ply);
	mlx_loop(win.mlx);
}
