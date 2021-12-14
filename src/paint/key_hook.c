/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:52:31 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/08 14:58:13 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paint.h"

static void	scape_key(t_win *win)
{
	mlx_clear_window(win->mlx, win->mlx_win);
	mlx_destroy_window(win->mlx, win->mlx_win);
	free_mapi(win->mapi);
	exit (0);
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
	return (0);
}
