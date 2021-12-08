/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:34:23 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/08 19:20:18 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paint.h"

void	ray_loop(t_player *ply)
{
	int		x;
	t_ray	*ray;

	ray = (t_ray *) malloc(sizeof(t_ray) * SCR_W);
	x = 0;
	while (x < SCR_W - 1)
	{
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

		x++;
	}
}