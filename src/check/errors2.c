/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 20:02:12 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/04 20:02:35 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"

void	error_incorrect_char_in_map(t_map *mapi, char **map)
{
	ft_putstr_fd("Cub3D error: incorrect char in map.\n", 2);
	free_mapi_and_map(mapi, map);
	exit (42);
}