/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:45:50 by tomartin          #+#    #+#             */
/*   Updated: 2021/11/28 19:02:24 by tomartin         ###   ########.fr       */
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

typedef struct s_map{

	char	*NO_rute;
	char	*SO_rute;
	char	*WE_rute;
	char	*EA_rute;

	int		F_color[3];
	int		C_color[3];

	char	**map;
	
}	t_map;

int		open_map(int argc, char **argv);
char	**read_map(int fd_map, char *argv);

void	print_map(char **map);

#endif