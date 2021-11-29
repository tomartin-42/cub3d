/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:45:50 by tomartin          #+#    #+#             */
/*   Updated: 2021/11/29 10:05:50 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "mlx.h"
# include "libft.h"
# include "stdio.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# define EMPY 99999999999999

typedef struct s_map{
	char		*NO_rute;
	bool		have_NO;
	char		*SO_rute;
	bool		have_SO;
	char		*WE_rute;
	bool		have_WE;
	char		*EA_rute;
	bool		have_EA;

	long int	F_color[3];
	long int	C_color[3];

	char		**map;

}	t_map;

int		open_map(int argc, char **argv);
char	**read_map(int fd_map, char *argv);

void	load_map(t_map *mapi, char **map);

void	print_map(char **map);

#endif