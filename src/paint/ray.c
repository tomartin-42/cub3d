/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:34:23 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/09 12:58:52 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paint.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if ((x > 0 && x < 1919) && (y > 0 && y < 1079))
	{
		dst = data->addr + ((y) * data->line_length
				+ (x) * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

// while to print column
static void	print_line (t_data *data, int x, t_line *line)
{
	int	y;

	y = line[x].line_start;
	while(y < line[x].line_end)
	{
		my_mlx_pixel_put(data, x, y, GREEN);
		//printf("[[%d - %d]]\n", x, y);
		y++;
	}
}

void	ray_loop(t_player *ply, t_map *mapi, t_data *data)
{
	int		x;
	t_ray	*ray;
	t_line	*line;

	ray = (t_ray *) malloc(sizeof(t_ray) * SCR_W);
	line = (t_line *) malloc(sizeof(t_line) * SCR_W);
	x = 0;
	while (x < SCR_W - 1)
	{
		ray[x].hit = false;
		//calculate ray position and direction//
		ray[x].cameraX = 2 * x / (double)SCR_W - 1; //x-coordinate in camera space//
		ray[x].ray_D_x = ply->dir_ply.o.x + ply->camera.o.x * ray[x].cameraX;
		ray[x].ray_D_y = ply->dir_ply.o.y + ply->camera.o.y * ray[x].cameraX;

		//scuare init ray
		ray[x].ray_scuare_x = (int)ply->p_ply.x;
		ray[x].ray_scuare_y = (int)ply->p_ply.y;

		//length of ray from one x or y side to next x or y side
		if (ray[x].ray_D_x == 0)
			;	//ray[x].delta_x = (double)1 / 0.5;
		else
			ray[x].delta_x = sqrt(1 + (ray[x].ray_D_y * ray[x].ray_D_y)
				/ (ray[x].ray_D_x * ray[x].ray_D_x));
			//ray[x].delta_x = fabs(1 / ray[x].ray_D_x);
			
		if (ray[x].ray_D_y == 0)
			;	//ray[x].delta_y =  (double)1 / 0.5;
		else
			ray[x].delta_y = sqrt(1 + (ray[x].ray_D_y * ray[x].ray_D_x)
				/ (ray[x].ray_D_y * ray[x].ray_D_y));
			//ray[x].delta_x = fabs(1 / ray[x].ray_D_x);
			//ray[x].delta_y = fabs(1 / ray[x].ray_D_y);
		
		if(ray[x].ray_D_x < 0)
		{
			ray[x].step_x = -1;
			ray[x].side_D_x = ((int)ply->p_ply.x - ray[x].ray_scuare_x) * ray[x].delta_x;
		}
		else
		{
			ray[x].step_x = 1;
			ray[x].side_D_x = (ray[x].ray_scuare_x + 1.0 - ply->p_ply.x) * ray[x].delta_x;
		}
		if(ray[x].ray_D_y < 0)
		{
			ray[x].step_y = -1;
			ray[x].side_D_y = ((int)ply->p_ply.y - ray[x].ray_scuare_y) * ray[x].delta_y;
		}
		else
		{
			ray[x].step_y = 1;
			ray[x].side_D_y = (ray[x].ray_scuare_y + 1.0 - ply->p_ply.y) * ray[x].delta_y;
		}

		while (ray[x].hit == 0)
		{
			/*printf("hit: %d\n", ray[x].hit);
			printf("ray_d_x: %f\n", ray[x].ray_D_x);
			printf("ray_d_y: %f\n", ray[x].ray_D_y);
			printf("dir_ply_x: %f\n", ply->dir_ply.o.x);
			printf("dir_ply_y: %f\n", ply->dir_ply.o.y);
			printf("ray_square_x: %d\n", ray[x].ray_scuare_x);
			printf("dir_square_y: %d\n", ray[x].ray_scuare_y);
			printf("side_d_x: %f\n", ray[x].side_D_x);
			printf("side_d_y: %f\n", ray[x].side_D_y);
			printf("delta_d_x: %f\n", ray[x].delta_x);
			printf("delta_d_y: %f\n", ray[x].delta_y);*/
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
			if(mapi->map[ray[x].ray_scuare_x][ray[x].ray_scuare_y] == '1')
			{
				printf("x-->%d--\n", ray[x].ray_scuare_x);
				printf("y-->%d--\n", ray[x].ray_scuare_y);
				ray[x].hit = true;
			}
		}
		//Calculate distance of perpendicular ray
		if(ray[x].side == 0) 
			ray[x].wall_dist = (ray[x].side_D_x - ray[x].delta_x);
		else
			ray[x].wall_dist = (ray[x].side_D_y - ray[x].delta_y);
		/*printf("[[%f]]\n",ray[x].wall_dist);
		printf("[[x %f]]\n",ray[x].delta_x);
		printf("[[y %f]]\n",ray[x].delta_y);*/
		//Calculate height of line to draw on screen
		line[x].line_h = (SCR_H / ray[x].wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		line[x].line_start = -line[x].line_h / 2 + SCR_H / 2;
		if(line[x].line_start < 0)
			line[x].line_start = 0;
		line[x].line_end = line[x].line_h / 2 + SCR_H / 2;
		if(line[x].line_end >= SCR_H) 
			line[x].line_end = SCR_H - 1;
		print_line(data, x, line);

		x++;
	}
}
