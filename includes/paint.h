/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:51:49 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/14 12:20:00 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAINT_H
# define PAINT_H

# include "cube.h"

# define SCR_W 1280
# define SCR_H 720
# define SCL 100
# define STEP 0.2
# define ALFA 0.5
# define ROTATE_L	65361
# define ROTATE_R	65363
# define N_W 0
# define S_W 1
# define E_W 2
# define W_W 3
# define SIZE 100
# define GRAY 8947848
# define RED 16711680
# define GREEN 65280
# define BLUE 255
# define YELOW 16776960
# define CYAN 65535
# define FORWARD	119
# define BACK		115
# define RIGHT		100
# define LEFT		97

typedef struct s_d_point{
	double	x;
	double	y;
}	t_d_point;

typedef struct s_i_point{
	int		x;
	int		y;
}	t_i_point;

typedef struct s_d_vect{
	t_d_point	o;
}	t_vect;


typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;


// struct need to print colum to check rays
typedef struct	s_line{
	int	line_h;
	int line_start;
	int	line_end;
	int line_color;
}	t_line;

// p_player = point were is now the plyer
// dir_player = vetor direction player
// camera = vetor camera. Need perpendicular to dir_player vector
typedef struct s_player {
	t_vect		p_ply;
	t_vect		dir_ply;
	t_vect		camera;
}	t_player;

// ray_scuare_x and ..._y coordinate of the square where the ray is located
// side_x and ..._y distance the ray to first square x and y;
// delta_x and ..._y are the distance the ray has to travel to go 
//from 1 x-side to the next x-side, or from 1 y-side to the next y-side
// step_x and step_y is direction to step in x or y direction either +1 or -1
typedef struct s_ray
{
	int		ray_scuare_x;
	int		ray_scuare_y;
	double	ray_D_x; //ray dirextion v_x
	double	ray_D_y; //ray direction v_y
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	double 	cameraX; //camera coordinate x//
	int		step_x;
	int		step_y;
	bool	hit; //was there a wall hit?//
	int		side; //was a N_W ,S_W ,E_W or a W_W wall hit?//
	double	wall_dist;

}	t_ray;

typedef struct s_win{
	void		*mlx;
	void		*mlx_win;
	t_map		*mapi;
	t_data		*img;
	t_player	*ply;
}	t_win;

t_vect	sum_v(t_vect v_a, t_vect v_b);
t_vect	subtr_v(t_vect v_a, t_vect v_b);
double	mod_v(t_vect vect);
t_vect	proc_vect(t_vect v_a, double n);
void	load_values_v(t_vect *load, double x, double y);

void	paint_background(t_map *mapi, t_data *img);
void	ray_loop(t_player *player, t_map *mapi, t_data *data);

void	print_player(t_player *player);

int		key_hook(int keycode, t_win *win);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

int		transform_color(long int color[3]);

#endif
