/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openwindow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommy <tommy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:39:38 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/25 20:05:14 by tommy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paint.h"

static void	init_position_and_camera_vetor(t_map *mapi, t_player *ply)
{
	if (mapi->init_point == 'W')
	{
		load_values_v(&ply->dir_ply, 0, -1);
		load_values_v(&ply->camera, -0.66, 0);
	}
	else if (mapi->init_point == 'E')
	{
		load_values_v(&ply->dir_ply, 0, 1);
		load_values_v(&ply->camera, 0.66, 0);
	}
	else if (mapi->init_point == 'S')
	{
		load_values_v(&ply->dir_ply, 1, 0);
		load_values_v(&ply->camera, 0, -0.66);
	}
	else if (mapi->init_point == 'N')
	{
		load_values_v(&ply->dir_ply, -1, 0);
		load_values_v(&ply->camera, 0, 0.66);
	}
}

static t_player	*init_ply(t_map *mapi)
{
	t_player	*ply;

	ply = malloc (sizeof(t_player));
	ply->p_ply.o.x = (double)(mapi->xy_init_point[1] + 0.5);
	ply->p_ply.o.y = (double)(mapi->xy_init_point[0] + 0.5);
	init_position_and_camera_vetor(mapi, ply);
	return (ply);
}

void	paint_background(t_map *mapi, t_data *img)
{
	int	color_f;
	int	color_c;
	int	i;
	int	j;

	color_c = transform_color(mapi->c_color);
	color_f = transform_color(mapi->f_color);
	i = 0;
	while (i < SCR_W -1)
	{
		j = 0;
		while (j < SCR_H - 1)
		{
			if (j < (SCR_H / 2))
				my_mlx_pixel_put(img, i, j, color_c);
			else
				my_mlx_pixel_put(img, i, j, color_f);
			j++;
		}
		i++;
	}
}

static void	init_p_win(t_map *mapi, t_player *ply, t_data *img, t_win *win)
{
	win->mapi = mapi;
	win->img = img;
	win->ply = ply;
	win->mapi = mapi;
	win->k_f = false;
	win->k_b = false;
	win->k_r = false;
	win->k_l = false;
	win->r_r = false;
	win->r_l = false;
	win->mlx = mlx_init();
}

void	init_window(t_map *mapi, char *argv)
{
	t_win		win;
	t_data		img;
	t_player	*ply;

	ply = init_ply(mapi);
	init_p_win(mapi, ply, &img, &win);
	win.mlx_win = mlx_new_window(win.mlx, SCR_W, SCR_H, argv);
	img.img = mlx_new_image(win.mlx, SCR_W, SCR_H);
	get_textures(&win, mapi);
	mlx_hook(win.mlx_win, 17, 0, ft_close, &win);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	mlx_hook(win.mlx_win, 2, 1L << 0, ft_key_press, &win);
	mlx_loop_hook(win.mlx, ray_loop, &win);
	mlx_hook(win.mlx_win, 3, 1L << 1, ft_key_release, &win);
	mlx_put_image_to_window(win.mlx, win.mlx_win, img.img, 0, 0);
	mlx_loop(win.mlx);
}
