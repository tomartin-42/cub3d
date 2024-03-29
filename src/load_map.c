/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 17:52:45 by tomartin          #+#    #+#             */
/*   Updated: 2022/01/10 08:50:22 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "check.h"

void	generate_map_dp(int i, int j, t_map *mapi, char **map)
{
	int	k;
	int	size;

	k = 0;
	size = i - j;
	mapi->map = (char **) malloc(sizeof(char *) * (size + 1));
	mapi->map[size] = NULL;
	while (j < i)
	{
		mapi->map[k] = ft_strdup(map[j]);
		j++;
		k++;
	}
}

static void	get_map_continue(int *i, char **map)
{
	char	*aux;

	while (map[*i])
	{
		aux = ft_strtrim(map[*i], " /t");
		if (!ft_strlen(aux))
		{
			free(aux);
			break ;
		}
		free(aux);
		(*i)++;
	}
}

void	get_map(int i, t_map *mapi, char **map)
{
	char	*aux;
	int		j;	

	aux = NULL;
	while (map[i])
	{
		aux = ft_strtrim(map[i], " /t");
		if (ft_strlen(aux))
		{
			free(aux);
			break ;
		}
		free(aux);
		i++;
	}
	j = i;
	get_map_continue(&i, map);
	generate_map_dp(i, j, mapi, map);
}

/* - Parses every line of the map looking for the information needed
 * to run the cub3d program. It does not need any order in the parameters
 * (textures dont have to come in an specific order).
 * - Splits every line in tabs/spaces, and then checks for every keyword
 * defining the information on each line, for example, NO, SO, etc. 
 * - Extracts this information to be then propperly used.*/
void	load_map(t_map *mapi, char **map)
{
	int		i;
	char	**line;

	i = 0;
	while (map[i])
	{
		line = split_line(map[i]);
		get_files_colors(line, mapi, map[i], map);
		ft_free_dp(line);
		i++;
		if (!check_param_map(mapi))
			break ;
	}
	if (check_param_map(mapi))
	{
		ft_putstr_fd("Cub3D error: miss param in file\n", 2);
		free_mapi_and_map(mapi, map);
		exit (42);
	}
	else
		get_map(i, mapi, map);
}

/* Checks if all the parameters have been loaded into the mapi struct,
 * otherwise it continues. This is in order to start parsing the map
 * only when we have the information we need. */
int	check_param_map(t_map *mapi)
{
	int	ret;

	ret = 0;
	if (mapi->has_no == false)
		ret = 1;
	if (mapi->has_so == false)
		ret = 1;
	if (mapi->has_we == false)
		ret = 1;
	if (mapi->has_ea == false)
		ret = 1;
	if (mapi->f_color[0] == EMPTY || mapi->f_color[1] == EMPTY
		|| mapi->f_color[2] == EMPTY)
		ret = 1;
	if (mapi->c_color[0] == EMPTY || mapi->c_color[1] == EMPTY
		|| mapi->c_color[2] == EMPTY)
		ret = 1;
	return (ret);
}
