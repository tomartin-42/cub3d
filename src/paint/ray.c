/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:34:23 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/26 18:17:01 by tomartin         ###   ########.fr       */
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

// while to print column
static inline void	print_line(t_data *data, int x, t_line *line, t_win *win)
{
	int			y;
	int			color;
	int			resp;
	int			ty;

	ty = line[x].line_color;
	y = line[x].line_start;
	while (y < line[x].line_end)
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

//Calculate distance of perpendicular to ray
//Calculate height of line to draw on screen
//calculate lowest and highest pixel to fill in current stripe
static void	calc_dist_and_colum(t_ray *ray, t_win *win, int x, t_line *line)
{
	if (ray[x].side == 0)
		ray[x].wall_dist = (double)(ray[x].ray_scuare_x
				- win->ply->p_ply.o.x + (1 - (double)ray[x].step_x) / 2)
			/ ray[x].ray_d_x;
	else
		ray[x].wall_dist = (double)(ray[x].ray_scuare_y
				- win->ply->p_ply.o.y + (1 - (double)ray[x].step_y) / 2)
			/ ray[x].ray_d_y;
	line[x].line_h = (SCR_H / ray[x].wall_dist);
	line[x].line_start = -line[x].line_h / 2 + SCR_H / 2;
	if (line[x].line_start < 0)
		line[x].line_start = 0;
	line[x].line_end = line[x].line_h / 2 + SCR_H / 2;
	if (line[x].line_end >= SCR_H || line[x].line_end < 0)
		line[x].line_end = SCR_H - 1;
}

//calculate value of wall_x
//x coordinate on the texture
static void	calc_wall_x(t_ray *ray, t_win *win, int x, int ty)
{
	if (ray[x].side == 0)
		ray[x].wall_x = win->ply->p_ply.o.y + ray[x].wall_dist * ray[x].ray_d_y;
	else
		ray[x].wall_x = win->ply->p_ply.o.x + ray[x].wall_dist * ray[x].ray_d_x;
	ray[x].wall_x -= floor(ray[x].wall_x);
	win->text[ty].text_x = (int)(ray[x].wall_x * (double)(win->text[ty].width));
	if (ray[x].side == 0 && ray[x].ray_d_x > 0)
		win->text[ty].text_x = win->text[ty].width - win->text[ty].text_x - 1;
	if (ray[x].side == 1 && ray[x].ray_d_y < 0)
		win->text[ty].text_x = win->text[ty].width - win->text[ty].text_x - 1;
}

int	ray_loop(t_win *win)
{
	int		x;
	t_ray	*ray;
	t_line	*line;
	int		ty;

	ray = (t_ray *) malloc(sizeof(t_ray) * SCR_W);
	line = (t_line *) malloc(sizeof(t_line) * SCR_W);
	x = 0;
	paint_background(win->mapi, win->img);
	while (x < SCR_W - 1)
	{
		init_values_ray(win->ply, ray, x);
		calculate_step_and_side(win->ply, ray, x);
		dda_loop(ray, win->mapi, x);
		ty = calculate_wall_texture(ray, x);
		calc_dist_and_colum(ray, win, x, line);
		calc_wall_x(ray, win, x, ty);
		calc_text_increase(win, line, x, ty);
		print_line(win->img, x, line, win);
		x++;
	}
	mlx_put_image_to_window(win->mlx, win->mlx_win, win->img->img, 0, 0);
	main_moves(win);
	free_ray_and_line(ray, line);
	return (0);
}
