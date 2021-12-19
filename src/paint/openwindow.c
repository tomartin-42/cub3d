/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openwindow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:39:38 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/19 17:47:14 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paint.h"

static int	ft_close(t_win *win)
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
	ply->p_ply.o.x = (double)(mapi->xy_init_point[1] + 0.5);
	ply->p_ply.o.y = (double)(mapi->xy_init_point[0] + 0.5);
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
	return (ply);
}

void	paint_background(t_map *mapi, t_data *img)
{
	int	color_F;
	int	color_C;
	int	i;
	int	j;

	color_C = transform_color(mapi->C_color);
	color_F = transform_color(mapi->F_color);
	i = 0;
	while (i < SCR_W -1)
	{
		j = 0;
		while (j < SCR_H - 1)
		{
			if (j < (SCR_H / 2))
				my_mlx_pixel_put(img, i, j, color_C);
			else
				my_mlx_pixel_put(img, i, j, color_F);
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
	win->mlx = mlx_init();
	win->keys->m_f = false;
	win->keys->m_b = false;
	win->keys->m_r = false;
	win->keys->m_l = false;
	win->keys->r_r = false;
	win->keys->r_l = false;
}

static void	get_texture_addr(t_data *text)
{
	text[0].addr = mlx_get_data_addr(text[0].img, &text[0].bits_per_pixel,
			&text[0].line_length, &text[0].endian);
	text[1].addr = mlx_get_data_addr(text[1].img, &text[1].bits_per_pixel,
			&text[1].line_length, &text[1].endian);
	text[2].addr = mlx_get_data_addr(text[2].img, &text[2].bits_per_pixel,
			&text[2].line_length, &text[2].endian);
	text[3].addr = mlx_get_data_addr(text[3].img, &text[3].bits_per_pixel,
			&text[3].line_length, &text[3].endian);
}

static void	get_texture(t_win *win, t_map *mapi)
{
	t_data	text[4];

	text[0].img = mlx_xpm_file_to_image(win->mlx, mapi->NO_rute,
			&text[0].width, &text[0].height);
	text[1].img = mlx_xpm_file_to_image(win->mlx, mapi->EA_rute,
			&text[1].width, &text[1].height);
	text[2].img = mlx_xpm_file_to_image(win->mlx, mapi->SO_rute,
			&text[2].width, &text[2].height);
	text[3].img = mlx_xpm_file_to_image(win->mlx, mapi->WE_rute,
			&text[3].width, &text[3].height);
	get_texture_addr(text);
}

void	init_window(t_map *mapi, char *argv)
{
	t_win		win;
	t_data		img;
//	t_data		text[4];
	t_player	*ply;

	ply = init_ply(mapi);
	init_p_win(mapi, ply, &img, &win);
	win.mlx_win = mlx_new_window(win.mlx, SCR_W, SCR_H, argv);
	img.img = mlx_new_image(win.mlx, SCR_W, SCR_H);
//	mlx_key_hook(win.mlx_win, key_hook, &win);
	get_texture(&win, mapi);
	mlx_hook(win.mlx_win, 17, 0, ft_close, &win);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	//paint_background(mapi, &img); 
	//ray_loop(&win);
	mlx_hook(win.mlx_win, 2, 1L << 0, ft_key_press, &win);
	mlx_loop_hook(win.mlx, ray_loop, &win);
	mlx_hook(win.mlx_win, 3, 1L << 1, ft_key_release, &win);
	mlx_put_image_to_window(win.mlx, win.mlx_win, img.img, 0, 0);
	//print_player(ply);
	mlx_loop(win.mlx);
}
