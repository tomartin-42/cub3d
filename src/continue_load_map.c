/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_load_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 08:53:28 by tomartin          #+#    #+#             */
/*   Updated: 2022/01/10 08:50:43 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "check.h"

/* Loads the line corresponding to the colors F or C into the mapi struct. */
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
	if (*col == mapi->c_color)
		mapi->has_c = true;
	else
		mapi->has_f = true;
	ft_free_dp(num);
}

/* Gets a line (which we already know start by F/C, then parses the numbers
 * following. Raises error if a line starting by F or C was already found
 * before. */
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
		if (mapi->has_f == true)
			error_repeated_parameter_entry(mapi, map);
		load_color(num, mapi, map, &mapi->f_color);
	}
	if (!ft_strcmp(line[0], "C"))
	{
		if (mapi->has_c == true)
			error_repeated_parameter_entry(mapi, map);
		load_color(num, mapi, map, &mapi->c_color);
	}
}

/* Norminette moment*/
void	get_route(char *line, char **route, bool *flag)
{
	free(*route);
	*route = ft_strdup(line);
	*flag = true;
}

/* Depending on the variable flag, loads the texture paths to the corresponing
 * entry inside the mapi struct. In case a texture path title (NO,SO,WE,EA) is
 * is repeated, raises an error. */
static void	complement_get_files(char *line, t_map *mapi, int flag, char **map)
{
	if (flag == 1)
	{
		if (mapi->has_no == true)
			error_repeated_parameter_entry(mapi, map);
		get_route(line, &mapi->no_route, &mapi->has_no);
	}
	if (flag == 2)
	{
		if (mapi->has_so == true)
			error_repeated_parameter_entry(mapi, map);
		get_route(line, &mapi->so_route, &mapi->has_so);
	}
	if (flag == 3)
	{
		if (mapi->has_we == true)
			error_repeated_parameter_entry(mapi, map);
		get_route(line, &mapi->we_route, &mapi->has_we);
	}
	if (flag == 4)
	{
		if (mapi->has_ea == true)
			error_repeated_parameter_entry(mapi, map);
		get_route(line, &mapi->ea_route, &mapi->has_ea);
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
