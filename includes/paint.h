/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:51:49 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/06 17:27:41 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAINT_H
# define PAINT_H

# include "cube.h"

# define SCR_W 1920
# define SCR_H 1080
# define SCL 100

typedef struct s_point{
	float	x;
	float	y;
}	t_point;

typedef struct s_vect{
	t_point	o;
}	t_vect;

typedef struct s_win{
	void	*mlx;
	void	*mlx_win;
}	t_win;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_player {
	t_point	p_player;
	t_vect	dir_player;
	t_vect	camera;
}	t_player;

t_vect	sum_v(t_vect v_a, t_vect v_b);
t_vect	subtr_v(t_vect v_a, t_vect v_b);
float	mod_v(t_vect vect);
t_vect	proc_vect(t_vect v_a, float n);
void	load_values_v(t_vect *load, float x, float y);

void	print_player(t_player *player);

#endif