/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:52:31 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/15 10:55:25 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paint.h"
#include "keys.h"

static void	scape_key(t_win *win)
{
	mlx_clear_window(win->mlx, win->mlx_win);
	mlx_destroy_window(win->mlx, win->mlx_win);
	free_mapi(win->mapi);
	exit (0);
}

static void rotate_r(t_win *win)
{
		double	x1;
		double	y1;

		x1 = (cos(-ALFA) * win->ply->dir_ply.o.x) 
			- (sin(-ALFA) * win->ply->dir_ply.o.y);
		y1 = (sin(-ALFA) * win->ply->dir_ply.o.x) 
			+ (cos(-ALFA) * win->ply->dir_ply.o.y);
		load_values_v(&win->ply->dir_ply, x1, y1);
		x1 = (cos(-ALFA) * win->ply->camera.o.x) 
			- (sin(-ALFA) * win->ply->camera.o.y);
		y1 = (sin(-ALFA) * win->ply->camera.o.x) 
			+ (cos(-ALFA) * win->ply->camera.o.y);
		load_values_v(&win->ply->camera, x1, y1);
		//paint_background(win->mapi, win->img);
		//ray_loop(win->ply, win->mapi, win->img);
		//mlx_put_image_to_window(win->mlx, win->mlx_win, win->img->img, 0, 0);
}

static void	rotate_l(t_win *win)
{
		double	x1;
		double	y1;

		x1 = (cos(ALFA) * win->ply->dir_ply.o.x) 
			- (sin(ALFA) * win->ply->dir_ply.o.y);
		y1 = (sin(ALFA) * win->ply->dir_ply.o.x) 
			+ (cos(ALFA) * win->ply->dir_ply.o.y);
		load_values_v(&win->ply->dir_ply, x1, y1);
		x1 = (cos(ALFA) * win->ply->camera.o.x) 
			- (sin(ALFA) * win->ply->camera.o.y);
		y1 = (sin(ALFA) * win->ply->camera.o.x) 
			+ (cos(ALFA) * win->ply->camera.o.y);
		load_values_v(&win->ply->camera, x1, y1);
		//paint_background(win->mapi, win->img);
		//ray_loop(win->ply, win->mapi, win->img);
		//mlx_put_image_to_window(win->mlx, win->mlx_win, win->img->img, 0, 0);
}

int	key_hook(int keycode, t_win *win)
{
	if (keycode == 53)
		scape_key(win);
	else if (keycode == FORWARD)
	{
		win->ply->p_ply.o.y += 0.2;
		paint_background(win->mapi, win->img);
		ray_loop(win->ply, win->mapi, win->img);
		mlx_put_image_to_window(win->mlx, win->mlx_win, win->img->img, 0, 0);
	}
	else if (keycode == BACK)
	{
		win->ply->p_ply.o.y -= 0.2;
		paint_background(win->mapi, win->img);
		ray_loop(win->ply, win->mapi, win->img);
		mlx_put_image_to_window(win->mlx, win->mlx_win, win->img->img, 0, 0);
	}
	else if (keycode == RIGHT)
	{
		win->ply->p_ply.o.x += 0.2;
		paint_background(win->mapi, win->img);
		ray_loop(win->ply, win->mapi, win->img);
		mlx_put_image_to_window(win->mlx, win->mlx_win, win->img->img, 0, 0);
	}
	else if (keycode == LEFT)
	{
		win->ply->p_ply.o.x -= 0.2;
		paint_background(win->mapi, win->img);
		ray_loop(win->ply, win->mapi, win->img);
		mlx_put_image_to_window(win->mlx, win->mlx_win, win->img->img, 0, 0);
	}
	else if (keycode == ROTATE_R)
		rotate_r(win);
	else if (keycode == ROTATE_L)
		rotate_l(win);
	paint_background(win->mapi, win->img);
	ray_loop(win->ply, win->mapi, win->img);
	mlx_put_image_to_window(win->mlx, win->mlx_win, win->img->img, 0, 0);
	return (0);
}
