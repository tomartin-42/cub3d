/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:52:31 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/18 13:36:49 by tomartin         ###   ########.fr       */
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

int	ft_key_press(int keycode, t_win *win)
{
	if (keycode == 53)
		scape_key(win);
	else if (keycode == FORWARD)
		win->keys->m_f = true;
	else if (keycode == BACK)
		win->keys->m_b = true;
	else if (keycode == RIGHT)
		win->keys->m_r = true;
	else if (keycode == LEFT)
		win->keys->m_l = true;
	else if (keycode == ROTATE_R)
		win->keys->r_r = true;
	else if (keycode == ROTATE_L)
		win->keys->r_l = true;
	return (0);
}

int	ft_key_release(int keycode, t_win *win)
{
	if (keycode == 53)
		scape_key(win);
	else if (keycode == FORWARD)
		win->keys->m_f = false;
	else if (keycode == BACK)
		win->keys->m_b = false;
	else if (keycode == RIGHT)
		win->keys->m_r = false;
	else if (keycode == LEFT)
		win->keys->m_l = false;
	else if (keycode == ROTATE_R)
		win->keys->r_r = false;
	else if (keycode == ROTATE_L)
		win->keys->r_l = false;
	return (0);
}
