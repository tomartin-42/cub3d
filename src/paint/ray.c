/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:34:23 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/08 20:33:03 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paint.h"

void	ray_loop(t_player *ply, t_map *mapi)
{
	int		x;
	t_ray	*ray;

	ray = (t_ray *) malloc(sizeof(t_ray) * SCR_W);
	x = 0;
	while (x < SCR_W - 1)
	{
		ray[x].hit = false;
		//calculate ray position and direction//
		ray[x].cameraX = (double)(2 * x) / (SCR_W - 1); //x-coordinate in camera space//
		ray[x].ray_D_x = ply->dir_ply.o.x + ply->camera.o.x * ray[x].cameraX;
		ray[x].ray_D_y = ply->dir_ply.o.y + ply->camera.o.y * ray[x].cameraX;

		//scuare init ray
		ray[x].ray_scuare_x = (int)ply->p_ply.x;
		ray[x].ray_scuare_y = (int)ply->p_ply.y;

		//length of ray from one x or y side to next x or y side
		//ray[x].delta_x = (ray[x].ray_D_x == 0) ? 1e30 : std::abs(1 / ray[x].ray_D_x);
		//ray[x].delta_y = (ray[x].ray_D_y == 0) ? 1e30 : std::abs(1 / ray[x].ray_D_y);
		
		if(ray[x].ray_D_x < 0)
		{
			ray[x].step_x = -1;
			ray[x].side_D_x = ((int)ply->p_ply.x - ray[x].ray_scuare_x) * ray[x].delta_x;
		}
		else
		{
			ray[x].step_x = 1;
			ray[x].side_D_x = (ray[x].ray_scuare_x + 1.0 - (int)ply->p_ply.x) * ray[x].delta_x;
		}
		if(ray[x].ray_D_x < 0)
		{
			ray[x].step_y = -1;
			ray[x].side_D_y = ((int)ply->p_ply.y - ray[x].ray_scuare_y) * ray[x].delta_y;
		}
		else
		{
			ray[x].step_y = 1;
			ray[x].side_D_y = (ray[x].ray_scuare_y + 1.0 - (int)ply->p_ply.y) * ray[x].delta_y;
		}

		while (ray[x].hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(ray[x].side_D_x < ray[x].side_D_y)
			{
				ray[x].side_D_x += ray[x].delta_x;
				ray[x].ray_scuare_x += ray[x].step_x;
				ray[x].side = 0;
			}
			else
			{
				ray[x].side_D_y += ray[x].delta_y;
				ray[x].ray_scuare_y += ray[x].step_y;
				ray[x].side = 1;
			}
			//Check if ray has hit a wall
			if(mapi->map[ray[x].ray_scuare_x][ray[x].ray_scuare_y] == 1)
				ray[x].hit = 1;
		}
		//Calculate distance of perpendicular ray
		if(ray[x].side == 0) 
			ray[x].wall_dist = (ray[x].side_D_x - ray[x].delta_x);
		else
			ray[x].wall_dist = (ray[x].side_D_y - ray[x].delta_y);
		x++;
	}
}