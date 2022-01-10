/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 20:02:12 by tomartin          #+#    #+#             */
/*   Updated: 2022/01/10 08:45:59 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"

void	error_in_color_range(t_map *mapi, char **map)
{
	ft_putstr_fd("Cub3D error: color out of range [0,255]\n", 2);
	free_mapi_and_map(mapi, map);
	exit (42);
}

void	error_repeated_parameter_entry(t_map *mapi, char **map)
{
	ft_putstr_fd("Cub3D error: repeated texture or color in file.\n", 2);
	free_mapi_and_map(mapi, map);
	exit (42);
}

void	error_incorrect_char_in_map(t_map *mapi, char **map)
{
	ft_putstr_fd("Cub3D error: incorrect char in map.\n", 2);
	free_mapi_and_map(mapi, map);
	exit (42);
}

void	error_read_texture(t_map *mapi, char **map)
{
	ft_putstr_fd("Cub3D error: incorrect texture file or texture path.\n", 2);
	free_mapi_and_map(mapi, map);
	exit (42);
}
