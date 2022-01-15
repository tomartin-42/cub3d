/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:46:01 by tomartin          #+#    #+#             */
/*   Updated: 2022/01/15 14:26:42 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/* Auxiliar function to the initialization of the struct because norminette */
static t_map	*init_textures(t_map *aux_map)
{
	aux_map->no_route = ft_strdup("");
	aux_map->so_route = ft_strdup("");
	aux_map->we_route = ft_strdup("");
	aux_map->ea_route = ft_strdup("");
	aux_map->map = NULL;
	return (aux_map);
}

/* Initializes the struct used to parse the map content. */
static t_map	*init_mapi(void)
{
	t_map	*aux_map;

	aux_map = (t_map *) malloc(sizeof(t_map));
	aux_map->has_no = false;
	aux_map->has_so = false;
	aux_map->has_we = false;
	aux_map->has_ea = false;
	aux_map->has_f = false;
	aux_map->has_c = false;
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
	init_window(mapi, argv[1], map);
	free_mapi(mapi);
	ft_free_dp(map);
}
