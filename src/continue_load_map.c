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

static void	load_color_f(char **num, t_map *mapi, char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (num[i])
	{
		if (ft_strlen(num[i]))
		{
			mapi->f_color[j] = ft_atoi(num[i]);
			if (mapi->f_color[j] < 0 || mapi->f_color[j] > 255)
			{
				ft_putstr_fd("Cub3D error: incorrect color\n", 2);
				free_mapi_and_map(mapi, map);
				exit (42);
			}
			j++;
		}
		i++;
	}
	mapi->have_F = true;
}

static void	load_color_c(char **num, t_map *mapi, char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (num[i])
	{
		if (ft_strlen(num[i]))
		{
			mapi->c_color[j] = ft_atoi(num[i]);
			if (mapi->c_color[j] < 0 || mapi->c_color[j] > 255)
			{
				ft_putstr_fd("Cub3D error: incorrect color\n", 2);
				free_mapi_and_map(mapi, map);
				exit (42);
			}
			j++;
		}
		i++;
	}
	mapi->have_F = true;
}

static void	get_colors(char **line, t_map *mapi, char *c_line, char **map)
{
	char	**num;
	char	*aux;
	int		i;

	i = 0;
	num = ft_split(c_line, ',');
	while (num[i])
	{
		aux = ft_strtrim(num[i], " ,CF\t");
		free(num[i]);
		num[i] = ft_strdup(aux);
		free(aux);
		i++;
	}
	if (!ft_strcmp(line[0], "F"))
		load_color_f(num, mapi, map);
	if (!ft_strcmp(line[0], "C"))
		load_color_c(num, mapi, map);
	ft_free_dp(num);
}

static void	complement_get_files(char *line, t_map *mapi, int select)
{
	printf("*%s*\n", line);
	if (select == 1)
	{
		free(mapi->NO_rute);
		mapi->NO_rute = ft_strtrim(line, " \t");
		mapi->have_NO = true;
	}
	if (select == 2)
	{
		free(mapi->SO_rute);
		mapi->SO_rute = ft_strtrim(line, " \t");
		mapi->have_SO = true;
	}
	if (select == 3)
	{
		free(mapi->WE_rute);
		mapi->WE_rute = ft_strtrim(line, " \t");
		mapi->have_WE = true;
	}
	if (select == 4)
	{
		free(mapi->EA_rute);
		mapi->EA_rute = ft_strtrim(line, " \t");
		mapi->have_EA = true;
	}
}

//This function get texture files and line colors and distributed
void	get_files_colors(char **line, t_map *mapi, char *c_line, char **map)
{
	char	*aux;

	aux = ft_strtrim(line[0], " \t");
	if (line != NULL && line[0] != NULL && line[1] != NULL)
	{
		if (!ft_strcmp(aux, "NO") && mapi->have_NO == false)
			complement_get_files(line[1], mapi, 1);
		else if (!ft_strcmp(aux, "SO") && mapi->have_SO == false)
			complement_get_files(line[1], mapi, 2);
		else if (!ft_strcmp(aux, "WE") && mapi->have_WE == false)
			complement_get_files(line[1], mapi, 3);
		else if (!ft_strcmp(aux, "EA") && mapi->have_EA == false)
			complement_get_files(line[1], mapi, 4);
		else if (!ft_strcmp(aux, "F") && mapi->have_F == false)
			get_colors(line, mapi, c_line, map);
		else if (!ft_strcmp(aux, "C") && mapi->have_C == false)
			get_colors(line, mapi, c_line, map);
	}
	free(aux);
}
