/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommy <tommy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:34:23 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/25 18:37:46 by tommy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paint.h"

static inline void	my_mlx_pixel_put1(t_data *data, int x, int y, int color)
{
	char	*dst;

	if ((x > 0 && x < SCR_W - 1) && (y > 0 && y < SCR_H - 1))
	{
		dst = data->addr + ((y) * data->line_length
				+ (x) * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

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
	int			y;
	int			color;
	int			resp;
	int			ty;

	ty = line[x].line_color;
	y = line[x].line_start;
	while(y < line[x].line_end)
	{
		win->text[ty].text_y = (int)win->text[ty].text_pos
			& (win->text[ty].height - 1);
		win->text[ty].text_pos += win->text[ty].step;
		color = ((win->text[ty].text_y * win->text[ty].line_length) 
			+ win->text[ty].text_x * (win->text[ty].bits_per_pixel / 8));
		resp = *(int *)(win->text[ty].addr + (int)color);
		my_mlx_pixel_put1(data, x, y, resp);
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

//Calculate texture wall
static int calculate_wall_texture(t_ray *ray, int x)
{
	int	text_type;

	if (ray[x].side == 0 && ray[x].ray_D_x < 0)
		text_type = N_W;
	if (ray[x].side == 0 && ray[x].ray_D_x >= 0)
		text_type = E_W; 
	if (ray[x].side == 1 && ray[x].ray_D_y < 0)
		text_type = S_W; 
	if (ray[x].side == 1 && ray[x].ray_D_y >= 0)
		text_type = W_W; 
	return (text_type);
}

int	ray_loop(t_win *win)
{
	int		x;
	t_ray	*ray;
	t_line	*line;
	int		ty;
	double	wall_x;

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
		ty = calculate_wall_texture(ray, x);
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
		if (ray[x].side == 0)
			wall_x = win->ply->p_ply.o.y + ray[x].wall_dist * ray[x].ray_D_y;
		else
			wall_x = win->ply->p_ply.o.x + ray[x].wall_dist * ray[x].ray_D_x;
		wall_x -= floor((wall_x));
		//x coordinate on the texture
		win->text[ty].text_x =(int)(wall_x * (double)(win->text[ty].width));
		if (ray[x].side == 0 && ray[x].ray_D_x > 0)
			win->text[ty].text_x = win->text[ty].width - win->text[ty].text_x - 1;
		if (ray[x].side == 1 && ray[x].ray_D_y < 0)
			win->text[ty].text_x = win->text[ty].width - win->text[ty].text_x - 1;
		// How much to increase the texture coordinate per screen pixel
		win->text[ty].step = 1.0 * win->text[ty].height / line[x].line_h;
		// Starting texture coordinate
		win->text[ty].text_pos = (line[x].line_start - SCR_H / 2
				+ line[x].line_h / 2) * win->text[ty].step; 
		//===============================================================
		line[x].line_color = ty;
	//	printf("x = %i\n", x);
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
