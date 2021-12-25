/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommy <tommy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:52:31 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/25 20:01:31 by tommy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paint.h"
#include "keys.h"

int	ft_close(t_win *win)
{
	mlx_destroy_window(win->mlx, win->mlx_win);
	free_mapi(win->mapi);
	exit (0);
	return (0);
}

static void	scape_key(t_win *win)
{
	mlx_clear_window(win->mlx, win->mlx_win);
	mlx_destroy_window(win->mlx, win->mlx_win);
	free_mapi(win->mapi);
	exit (0);
}

int	ft_key_press(int keycode, t_win *win)
{
	if (keycode == 53)
		scape_key(win);
	else if (keycode == FORWARD)
		win->k_f = true;
	else if (keycode == BACK)
		win->k_b = true;
	else if (keycode == RIGHT)
		win->k_r = true;
	else if (keycode == LEFT)
		win->k_l = true;
	else if (keycode == ROTATE_R)
		win->r_r = true;
	else if (keycode == ROTATE_L)
		win->r_l = true;
	return (0);
}

int	ft_key_release(int keycode, t_win *win)
{
	if (keycode == 53)
		scape_key(win);
	else if (keycode == FORWARD)
		win->k_f = false;
	else if (keycode == BACK)
		win->k_b = false;
	else if (keycode == RIGHT)
		win->k_r = false;
	else if (keycode == LEFT)
		win->k_l = false;
	else if (keycode == ROTATE_R)
		win->r_r = false;
	else if (keycode == ROTATE_L)
		win->r_l = false;
	return (0);
}
