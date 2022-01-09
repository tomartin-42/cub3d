/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_load_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 08:53:28 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/28 09:44:42 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "check.h"

static void	load_color(char **num, t_map *mapi, char **map, long int (*col)[3])
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (num[++i])
	{
		if (ft_strlen(num[i]))
		{
			(*col)[j] = ft_atoi(num[i]);
			if ((*col)[j] < 0 || (*col)[j] > 255)
				error_in_color_range(mapi, map);
			j++;
		}
	}
	//printf("*col: %p, c_color: %p, f_color: %p\n\n", *col, mapi->c_color, mapi->f_color);
	if (*col == mapi->c_color)
		mapi->has_C = true;
	else
		mapi->has_F = true;
	ft_free_dp(num);
}

void	get_route(char *line, char** route, bool* flag)
{
	free(*route);
	*route = ft_strdup(line);
	*flag = true;
}

static void	get_colors(char **line, t_map *mapi, char *c_line, char **map)
{
	char	**num;
	char	*aux;
	int		i;

	i = -1;
	num = ft_split(c_line, ',');
	while (num[++i])
	{
		aux = ft_strtrim(num[i], " ,CF\t");
		free(num[i]);
		num[i] = ft_strdup(aux);
		free(aux);
	}
	if (!ft_strcmp(line[0], "F"))
	{
		if (mapi->has_F == true)
			error_repeated_parameter_entry(mapi, map);
		load_color(num, mapi, map, &mapi->f_color);
	}
	if (!ft_strcmp(line[0], "C"))
	{
		if (mapi->has_C == true)
			error_repeated_parameter_entry(mapi, map);
		load_color(num, mapi, map, &mapi->c_color);
	}
}

static void	complement_get_files(char *line, t_map *mapi, int flag, char** map)
{
	if (flag == 1)
	{
		if (mapi->has_NO == true)
			error_repeated_parameter_entry(mapi, map);
		get_route(line, &mapi->NO_route, &mapi->has_NO);
	}
	if (flag == 2)
	{
		if (mapi->has_SO == true)
			error_repeated_parameter_entry(mapi, map);
		get_route(line, &mapi->SO_route, &mapi->has_SO);
	}
	if (flag == 3)
	{
		if (mapi->has_WE == true)
			error_repeated_parameter_entry(mapi, map);
		get_route(line, &mapi->WE_route, &mapi->has_WE);
	}
	if (flag == 4)
	{
		if (mapi->has_EA == true)
			error_repeated_parameter_entry(mapi, map);
		get_route(line, &mapi->EA_route, &mapi->has_EA);
	}
}

/* Checks for a line start corresponding to information that is needed to start
 * loading the game. One thing it does is it does not rewrite a parameter that
 * has already been parsed. This means, if you include two lines saying NO*/
void	get_files_colors(char **line, t_map *mapi, char *c_line, char **map)
{
	char	*aux;

	aux = ft_strdup(line[0]);
	if (line != NULL && line[0] != NULL && line[1] != NULL)
	{
		if (!ft_strcmp(aux, "NO"))
			complement_get_files(line[1], mapi, 1, map);
		else if (!ft_strcmp(aux, "SO"))
			complement_get_files(line[1], mapi, 2, map);
		else if (!ft_strcmp(aux, "WE"))
			complement_get_files(line[1], mapi, 3, map);
		else if (!ft_strcmp(aux, "EA"))
			complement_get_files(line[1], mapi, 4, map);
		else if (!ft_strcmp(aux, "F"))
			get_colors(line, mapi, c_line, map);
		else if (!ft_strcmp(aux, "C"))
			get_colors(line, mapi, c_line, map);
	}
	free(aux);
}
