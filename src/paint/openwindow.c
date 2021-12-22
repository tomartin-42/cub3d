/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openwindow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:39:38 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/22 09:14:06 by tomartin         ###   ########.fr       */
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
	win->k_f = false;
	win->k_b = false;
	win->k_r = false;
	win->k_l = false;
	win->r_r = false;
	win->r_l = false;
	win->mlx = mlx_init();
}

static void get_texture_addr(t_win *win)
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


static void	get_textures(t_win *win, t_map *mapi)
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
	printf("[0 text_w = %d]\n",win->text[0].width);
	printf("[0 text_h = %d]\n",win->text[0].height);
	printf("[0 text_bpp = %d]\n",win->text[0].bits_per_pixel);
	printf("[0 text_ll = %d]\n",win->text[0].line_length);
	printf("[0 text_end = %d]\n",win->text[0].endian);
	printf("=======================================\n");
	printf("[1 text_w = %d]\n",win->text[1].width);
	printf("[1 text_h = %d]\n",win->text[1].height);
	printf("[1 text_bpp = %d]\n",win->text[1].bits_per_pixel);
	printf("[1 text_ll = %d]\n",win->text[1].line_length);
	printf("[1 text_end = %d]\n",win->text[1].endian);
	printf("=======================================\n");
	printf("[2 text_w = %d]\n",win->text[2].width);
	printf("[2 text_h = %d]\n",win->text[2].height);
	printf("[2 text_bpp = %d]\n",win->text[2].bits_per_pixel);
	printf("[2 text_ll = %d]\n",win->text[2].line_length);
	printf("[2 text_end = %d]\n",win->text[2].endian);
	printf("=======================================\n");
	printf("[3 text_w = %d]\n",win->text[3].width);
	printf("[3 text_h = %d]\n",win->text[3].height);
	printf("[3 text_bpp = %d]\n",win->text[3].bits_per_pixel);
	printf("[3 text_ll = %d]\n",win->text[3].line_length);
	printf("[3 text_end = %d]\n",win->text[3].endian);
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
//	mlx_key_hook(win.mlx_win, key_hook, &win);
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
