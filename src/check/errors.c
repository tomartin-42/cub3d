/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 19:02:43 by tommy             #+#    #+#             */
/*   Updated: 2021/12/25 19:02:52 by tommy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"
#include "cube.h"

void	error_in_color_line(char **map, t_map *mapi)
{
	ft_putstr_fd("Cub3D error: error in color codificatión.\n", 2);
	free_mapi_and_map(mapi, map);
	exit (42);
}

void	error_miss_init_point(char **map, t_map *mapi)
{
	ft_putstr_fd("Cub3D error: miss init point.\n", 2);
	free_mapi_and_map(mapi, map);
	exit (42);
}

void	error_open_map(t_map *mapi, char **map)
{
	ft_putstr_fd("Cub3D error: open map.\n", 2);
	free_mapi_and_map(mapi, map);
	exit (42);
}

void	error_empty_map(void)
{
	ft_putstr_fd("Cub3D error: empty map.\n", 2);
	exit (42);
}

void	error_dual_init_point(t_map *mapi, char **map)
{
	ft_putstr_fd("Cub3D error: more than one init point.\n", 2);
	free_mapi_and_map(mapi, map);
	exit (42);
}
