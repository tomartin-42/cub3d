/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:34:23 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/08 18:31:47 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paint.h"

void	ray_loop(t_player *player)
{
	int		x;
	t_ray	*ray;

	ray = (t_ray *) malloc(sizeof(t_ray) * SCR_W);
	x = 0;
	while (x < SCR_W - 1)
	{
		//calculate ray position and direction//
		ray[x].cameraX = (double)(2 * x) / (SCR_W - 1); //x-coordinate in camera space//
		ray[x].ray_D_x = player->dir_player.o.x + player->camera.o.x * ray[x].cameraX;
		ray[x].ray_D_y = player->dir_player.o.y + player->camera.o.y * ray[x].cameraX;
		x++;
	}
}