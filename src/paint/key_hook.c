/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:52:31 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/16 11:56:19 by tomartin         ###   ########.fr       */
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
}

static void	move_f(t_win *win)
{	
	if(win->mapi->map[(int)(win->ply->p_ply.o.x 
		+ win->ply->dir_ply.o.x * STEP)][(int)(win->ply->p_ply.o.y)] != '1') 
		win->ply->p_ply.o.x += win->ply->dir_ply.o.x * STEP;
	if(win->mapi->map[(int)(win->ply->p_ply.o.x)]
		[(int)(win->ply->p_ply.o.y + win->ply->dir_ply.o.y * STEP)] != '1') 
		win->ply->p_ply.o.y += win->ply->dir_ply.o.y * STEP;
}

static void move_b(t_win *win)
{
	if(win->mapi->map[(int)(win->ply->p_ply.o.x 
		- win->ply->dir_ply.o.x * STEP)][(int)(win->ply->p_ply.o.y)] != '1') 
		win->ply->p_ply.o.x -= win->ply->dir_ply.o.x * STEP;
	if(win->mapi->map[(int)(win->ply->p_ply.o.x)]
		[(int)(win->ply->p_ply.o.y - win->ply->dir_ply.o.y * STEP)] != '1') 
		win->ply->p_ply.o.y -= win->ply->dir_ply.o.y * STEP;
}

static void	move_r(t_win *win)
{
	if(win->mapi->map[(int)(win->ply->p_ply.o.x 
		+ win->ply->dir_ply.o.y * STEP)][(int)(win->ply->p_ply.o.y)] != '1') 
		win->ply->p_ply.o.x += win->ply->dir_ply.o.y * STEP;
	if(win->mapi->map[(int)(win->ply->p_ply.o.x)]
		[(int)(win->ply->p_ply.o.y - win->ply->dir_ply.o.x * STEP)] != '1') 
		win->ply->p_ply.o.y -= win->ply->dir_ply.o.x * STEP;
}

static void move_l(t_win *win)
{
	if(win->mapi->map[(int)(win->ply->p_ply.o.x 
		- win->ply->dir_ply.o.y * STEP)][(int)(win->ply->p_ply.o.y)] != '1') 
		win->ply->p_ply.o.x -= win->ply->dir_ply.o.y * STEP;
	if(win->mapi->map[(int)(win->ply->p_ply.o.x)]
		[(int)(win->ply->p_ply.o.y + win->ply->dir_ply.o.x * STEP)] != '1') 
		win->ply->p_ply.o.y += win->ply->dir_ply.o.x * STEP;
}

int	key_hook(int keycode, t_win *win)
{
	if (keycode == 53)
		scape_key(win);
	else if (keycode == FORWARD)
		move_f(win);
	else if (keycode == BACK)
		move_b(win);
	else if (keycode == RIGHT)
		move_r(win);
	else if (keycode == LEFT)
		move_l(win);
	else if (keycode == ROTATE_R)
		rotate_r(win);
	else if (keycode == ROTATE_L)
		rotate_l(win);
	paint_background(win->mapi, win->img);
	ray_loop(win->ply, win->mapi, win->img);
	mlx_put_image_to_window(win->mlx, win->mlx_win, win->img->img, 0, 0);
	return (0);
}
