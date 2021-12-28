/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:45:50 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/28 10:22:39 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "mlx.h"
# include "libft.h"
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <math.h>

# define EMPTY 99999999999999

struct	s_ray;
struct	s_line;

typedef struct s_map{
	char		*NO_rute;
	bool		have_NO;
	char		*SO_rute;
	bool		have_SO;
	char		*WE_rute;
	bool		have_WE;
	char		*EA_rute;
	bool		have_EA;

	long int	f_color[3];
	bool		have_F;
	long int	c_color[3];
	bool		have_C;

	char		init_point;
	int			xy_init_point[2];
	int			map_widh;
	int			map_high;
	char		**map;
}	t_map;

int		open_map(int argc, char **argv);
char	**read_map(int fd_map, char *argv);

void	load_map(t_map *mapi, char **map);
void	get_files_colors(char **line, t_map *mapi, char *c_line, char **map);
int		check_param_map(t_map *mapi);

void	print_map(char **map);
void	print_struc_mapi(t_map *mapi);

void	main_check(t_map *mapi, char **map);

void	free_mapi(t_map *mapi);
void	free_mapi_and_map(t_map *mapi, char **map);

void	init_window(t_map *mapi, char *argv, char **map);

#endif
