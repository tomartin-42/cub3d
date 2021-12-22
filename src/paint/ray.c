/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:34:23 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/22 11:28:25 by tomartin         ###   ########.fr       */
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

// while to print column
static void	print_line (t_data *data, int x, t_line *line, t_win *win)
{
	int	y;
	uint32_t color;

	y = line[x].line_start;
	while(y < line[x].line_end)
	{
		win->text[1].text_y = (int)win->text[1].text_pos & (win->text[1].height - 1);
		win->text[1].text_pos += win->text[1].step;
		color = win->text[1].addr[win->text[1].height * win->text[1].text_x
			+ win->text[1].text_y];
		my_mlx_pixel_put(data, x, y, color);
//		my_mlx_pixel_put(data, x, y, line[x].line_color);
		y++;
	}
}

//calculate ray position and direction//
//scuare init ray
//length of ray from one x or y side to next x or y side
static void	init_values_ray(t_player *ply, t_ray *ray, int x)
{
	ray[x].cameraX = 2 * x / (double)SCR_W - 1; 
	ray[x].ray_D_x = ply->dir_ply.o.x + ply->camera.o.x * ray[x].cameraX;
	ray[x].ray_D_y = ply->dir_ply.o.y + ply->camera.o.y * ray[x].cameraX;
	ray[x].ray_scuare_x = (int)ply->p_ply.o.x;
	ray[x].ray_scuare_y = (int)ply->p_ply.o.y;
	ray[x].delta_x = fabs(1 / ray[x].ray_D_x);
	ray[x].delta_y = fabs(1 / ray[x].ray_D_y);
}

static void	calculate_step_and_side(t_player *ply, t_ray *ray, int x)
{
	if(ray[x].ray_D_x < 0)
	{
		ray[x].step_x = -1;
		ray[x].side_x = (double)(ply->p_ply.o.x - ray[x].ray_scuare_x) 
			* ray[x].delta_x;
	}
	else
	{
		ray[x].step_x = 1;
		ray[x].side_x = (double)(ray[x].ray_scuare_x + 1.0 - ply->p_ply.o.x) 
			* ray[x].delta_x;
	}
	if(ray[x].ray_D_y < 0)
	{
		ray[x].step_y = -1;
		ray[x].side_y = (double)(ply->p_ply.o.y - ray[x].ray_scuare_y) 
			* ray[x].delta_y;
	}
	else
	{
		ray[x].step_y = 1;
		ray[x].side_y = (double)(ray[x].ray_scuare_y + 1.0 - ply->p_ply.o.y) 
			* ray[x].delta_y;
	}
}

// DDA loop
//jump to next map square, either in x-direction, or in y-direction
//Check if ray has hit a wall
static void	dda_loop(t_ray *ray, t_map *mapi, int x)
{
	while (ray[x].hit == 0)
	{
		if(ray[x].side_x < ray[x].side_y)
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
		if(mapi->map[ray[x].ray_scuare_x][ray[x].ray_scuare_y] == '1')
			ray[x].hit = true;
	}
}

//Calculate wall color
static void calculate_color(t_ray *ray, t_line *line, int x)
{
	if (ray[x].side == 0 && ray[x].ray_D_x < 0)
		line[x].line_color = GRAY;
	if (ray[x].side == 0 && ray[x].ray_D_x >= 0)
		line[x].line_color = RED; 
	if (ray[x].side == 1 && ray[x].ray_D_y < 0)
		line[x].line_color = GREEN; 
	if (ray[x].side == 1 && ray[x].ray_D_y >= 0)
		line[x].line_color = BLUE; 
}

int	ray_loop(t_win *win)
{
	int		x;
	t_ray	*ray;
	t_line	*line;

	ray = (t_ray *) malloc(sizeof(t_ray) * SCR_W);
	line = (t_line *) malloc(sizeof(t_line) * SCR_W);
	x = 0;
	paint_background(win->mapi, win->img);
	while (x < SCR_W - 1)
	{
		init_values_ray(win->ply, ray, x);
		calculate_step_and_side(win->ply, ray, x);
		ray[x].hit = false;
		dda_loop(ray, win->mapi, x);
		calculate_color(ray, line, x);
		//Calculate distance of perpendicular to ray
		if(ray[x].side == 0) 
			ray[x].wall_dist = (double)(ray[x].ray_scuare_x 
				- win->ply->p_ply.o.x + (1 - (double)ray[x].step_x) / 2) 
				/ ray[x].ray_D_x;
		else
			ray[x].wall_dist = (double)(ray[x].ray_scuare_y 
				- win->ply->p_ply.o.y + (1 - (double)ray[x].step_y) / 2) 
				/ ray[x].ray_D_y;
		//Calculate height of line to draw on screen
		line[x].line_h = (SCR_H / ray[x].wall_dist);
		//calculate lowest and highest pixel to fill in current stripe
		line[x].line_start = -line[x].line_h / 2 + SCR_H / 2;
		if(line[x].line_start < 0)
			line[x].line_start = 0;
		line[x].line_end = line[x].line_h / 2 + SCR_H / 2;
		if(line[x].line_end >= SCR_H || line[x].line_end < 0) 
			line[x].line_end = SCR_H - 1;
		//===============================================================
		//calculate value of wall_x
		double	wall_x;
		if (ray[x].side == 0)
			wall_x = win->ply->p_ply.o.y + ray[x].wall_dist * ray[x].ray_D_y;
		else
			wall_x = win->ply->p_ply.o.x + ray[x].wall_dist * ray[x].ray_D_x;
		wall_x -= floor((wall_x));
		//x coordinate on the texture
		win->text[1].text_x =(int)(wall_x * (double)(win->text[1].width));
		if (ray[x].side == 0 && ray[x].ray_D_x > 0)
			win->text[1].text_x = win->text[1].width - win->text[1].text_x - 1;
		if (ray[x].side == 1 && ray[x].ray_D_y < 0)
			win->text[1].text_x = win->text[1].width - win->text[1].text_x - 1;
		// How much to increase the texture coordinate per screen pixel
		win->text[1].step = 1.0 * win->text[1].height / line[x].line_h;
		// Starting texture coordinate
		win->text[1].text_pos = (line[x].line_start - SCR_H / 2
				+ line[x].line_h / 2) * win->text[1].step; 
		//===============================================================

		print_line(win->img, x, line, win);
		x++;
	}
	mlx_put_image_to_window(win->mlx, win->mlx_win, win->img->img, 0, 0);
	move_f_b(win);
	move_r_l(win);
	rotate_r(win);
	rotate_l(win);
	free(ray);
	free(line);
	return (0);
}
