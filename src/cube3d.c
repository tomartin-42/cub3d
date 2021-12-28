/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:46:01 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/28 10:20:57 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static t_map	*init_textures(t_map *aux_map)
{
	aux_map->NO_rute = ft_strdup("");
	aux_map->SO_rute = ft_strdup("");
	aux_map->WE_rute = ft_strdup("");
	aux_map->EA_rute = ft_strdup("");
	aux_map->map = NULL;
	return (aux_map);
}

static t_map	*init_mapi(void)
{
	t_map	*aux_map;

	aux_map = (t_map *) malloc(sizeof(t_map));
	aux_map->have_NO = false;
	aux_map->have_SO = false;
	aux_map->have_WE = false;
	aux_map->have_EA = false;
	aux_map->have_F = false;
	aux_map->have_C = false;
	aux_map->f_color[0] = EMPTY;
	aux_map->f_color[1] = EMPTY;
	aux_map->f_color[2] = EMPTY;
	aux_map->c_color[0] = EMPTY;
	aux_map->c_color[1] = EMPTY;
	aux_map->c_color[2] = EMPTY;
	aux_map = init_textures(aux_map);
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
	main_check(mapi, map);
	print_map(map);
	printf("-----------------------------------------\n");
	print_struc_mapi(mapi);
	init_window(mapi, argv[1], map);
	free_mapi(mapi);
	ft_free_dp(map);
}
