/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_support.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:56:02 by tomartin          #+#    #+#             */
/*   Updated: 2022/01/10 10:10:13 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paint.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if ((x > 0 && x < SCR_W - 1) && (y > 0 && y < SCR_H - 1))
	{
		dst = data->addr + ((y) * data->line_length
				+ (x) * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

//calculate ray position and direction//
//scuare init ray
//length of ray from one x or y side to next x or y side
void	init_values_ray(t_player *ply, t_ray *ray, int x)
{
	ray[x].camera_x = 2 * x / (double)SCR_W - 1;
	ray[x].ray_d_x = ply->dir_ply.o.x + ply->camera.o.x * ray[x].camera_x;
	ray[x].ray_d_y = ply->dir_ply.o.y + ply->camera.o.y * ray[x].camera_x;
	ray[x].ray_scuare_x = (int)ply->p_ply.o.x;
	ray[x].ray_scuare_y = (int)ply->p_ply.o.y;
	ray[x].delta_x = fabs(1 / ray[x].ray_d_x);
	ray[x].delta_y = fabs(1 / ray[x].ray_d_y);
}

// DDA loop
//jump to next map square, either in x-direction, or in y-direction
//Check    ray has hit a wall
void	dda_loop(t_ray *ray, t_map *mapi, int x)
{		
	ray[x].hit = false;
	while (ray[x].hit == 0)
	{
		if (ray[x].side_x < ray[x].side_y)
		{
			ray[x].side_x += ray[x].delta_x;
			ray[x].ray_scuare_x += ray[x].step_x;
			ray[x].side = 0;
		}
		else
		{
			ray[x].side_y += ray[x].delta_y;
			ray[x].ray_scuare_y += ray[x].step_y;
			ray[x].side = 1;
		}
		if (mapi->map[ray[x].ray_scuare_x][ray[x].ray_scuare_y] == '1')
			ray[x].hit = true;
	}
}

void	calculate_step_and_side(t_player *ply, t_ray *ray, int x)
{
	if (ray[x].ray_d_x < 0)
	{
		ray[x].step_x = -1;
		ray[x].side_x = (double)(ply->p_ply.o.x
				- ray[x].ray_scuare_x) * ray[x].delta_x;
	}
	else
	{
		ray[x].step_x = 1;
		ray[x].side_x = (double)(ray[x].ray_scuare_x + 1.0
				- ply->p_ply.o.x) * ray[x].delta_x;
	}
	if (ray[x].ray_d_y < 0)
	{
		ray[x].step_y = -1;
		ray[x].side_y = (double)(ply->p_ply.o.y
				- ray[x].ray_scuare_y) * ray[x].delta_y;
	}
	else
	{
		ray[x].step_y = 1;
		ray[x].side_y = (double)(ray[x].ray_scuare_y + 1.0
				- ply->p_ply.o.y) * ray[x].delta_y;
	}
}

// How much to increase the texture coordinate per screen pixel
// Starting texture coordinate
void	calc_text_increase(t_win *win, t_line *line, int x, int ty)
{
	win->text[ty].step = 1.0 * win->text[ty].height / line[x].line_h;
	win->text[ty].text_pos = (line[x].line_start - SCR_H / 2
			+ line[x].line_h / 2) * win->text[ty].step;
	line[x].line_color = ty;
}
