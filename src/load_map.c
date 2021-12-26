/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 17:52:45 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/23 10:59:43 by tomartin         ###   ########.fr       */
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

void	get_map(int i, t_map *mapi, char **map)
{
	char	*aux;
	int		j;	

	aux = NULL;
	while (map[i])
	{
		aux = ft_strtrim(map[i], " /t");
		if (ft_strlen(aux))
			break ;
		free(aux);
		i++;
	}
	free(aux);
	j = i;
	while (map[i])
	{
		aux = ft_strtrim(map[i], " /t");
		if (!ft_strlen(aux))
			break ;
		free(aux);
		i++;
	}
	generate_map_dp(i, j, mapi, map);
}

void	load_map(t_map *mapi, char **map)
{
	int		i;
	char	**line;

	i = 0;
	while (map[i])
	{
		line = ft_split(map[i], ' ');
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

// check if all the parameters have been loaded into the mapi structure
// otherwise it continues to loop. It is necessary to
// know when start map matrix
int	check_param_map(t_map *mapi)
{
	int	ret;

	ret = 0;
	if (mapi->have_NO == false)
		ret = 1;
	if (mapi->have_SO == false)
		ret = 1;
	if (mapi->have_WE == false)
		ret = 1;
	if (mapi->have_EA == false)
		ret = 1;
	if (mapi->f_color[0] == EMPTY || mapi->f_color[1] == EMPTY
		|| mapi->f_color[2] == EMPTY)
		ret = 1;
	if (mapi->c_color[0] == EMPTY || mapi->c_color[1] == EMPTY
		|| mapi->c_color[2] == EMPTY)
		ret = 1;
	return (ret);
}
