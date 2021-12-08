/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:51:49 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/08 18:31:59 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAINT_H
# define PAINT_H

# include "cube.h"

# define SCR_W 1920
# define SCR_H 1080
# define SCL 100

typedef struct s_point{
	double	x;
	double	y;
}	t_point;

typedef struct s_vect{
	t_point	o;
}	t_vect;

typedef struct s_win{
	void	*mlx;
	void	*mlx_win;
	t_map	*mapi;
}	t_win;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

// p_player = point were is now the plyer
// dir_player = vetor direction player
// camera = vetor camera. Need perpendicular to dir_player vector
// ray_scuare_x and ..._y coordinate of the square where the ray is located
// side_D_x and ..._y distance the ray to first square x and y;
// delta_x and ..._y are the distance the ray has to travel to go 
//from 1 x-side to the next x-side, or from 1 y-side to the next y-side
typedef struct s_player {
	t_point	p_player;
	t_vect	dir_player;
	t_vect	camera;
}	t_player;

typedef struct s_ray
{
	int		ray_scuare_x;
	int		ray_scuare_y;
	double	ray_D_x;
	double	ray_D_y;
	double	side_D_x;
	double	side_D_y;
	double	delta_x;
	double	delta_y;
	double 	cameraX; //camera coordinate x//
}	t_ray;

t_vect	sum_v(t_vect v_a, t_vect v_b);
t_vect	subtr_v(t_vect v_a, t_vect v_b);
double	mod_v(t_vect vect);
t_vect	proc_vect(t_vect v_a, double n);
void	load_values_v(t_vect *load, double x, double y);

void	ray_loop(t_player *player);

void	print_player(t_player *player);

int		key_hook(int keycode, t_win *win);

#endif