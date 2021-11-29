/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:46:01 by tomartin          #+#    #+#             */
/*   Updated: 2021/11/29 10:04:44 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static t_map	*init_mapi(void)
{
	t_map	*aux_map;

	aux_map = (t_map *) malloc(sizeof(t_map));
	aux_map->have_NO = false;
	aux_map->have_SO = false;
	aux_map->have_WE = false;
	aux_map->have_EA = false;
	aux_map->F_color[0] = EMPY;
	aux_map->F_color[1] = EMPY;
	aux_map->F_color[2] = EMPY;
	aux_map->C_color[0] = EMPY;
	aux_map->C_color[1] = EMPY;
	aux_map->C_color[2] = EMPY;
	return (aux_map);
}

int	main(int argc, char **argv)
{
	int		fd_map;
	char	**map;
	t_map	*mapi;

	fd_map = open_map(argc, argv);
	map = read_map(fd_map, argv[1]);
	mapi = init_mapi();
	load_map(mapi, map);
	print_map(map);
}
