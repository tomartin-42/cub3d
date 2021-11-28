/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:45:50 by tomartin          #+#    #+#             */
/*   Updated: 2021/11/28 17:14:08 by tomartin         ###   ########.fr       */
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

int		open_map(int argc, char **argv);
char	**read_map(int fd_map, char *argv);

void	print_map(char **map);

#endif