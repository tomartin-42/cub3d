/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 08:53:28 by tomartin          #+#    #+#             */
/*   Updated: 2021/11/29 10:46:13 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	load_color_F(char **num, t_map *mapi)
{
	mapi->F_color[0] = ft_atoi(num[0]);
	mapi->F_color[1] = ft_atoi(num[1]);
	mapi->F_color[2] = ft_atoi(num[2]);
	if (mapi->F_color[0] < 0 || mapi->F_color[0] > 255)
		printf("ERROR INCORRECT COLOR\n");
	if (mapi->F_color[1] < 0 || mapi->F_color[1] > 255)
		printf("ERROR INCORRECT COLOR\n");
	if (mapi->F_color[2] < 0 || mapi->F_color[2] > 255)
		printf("ERROR INCORRECT COLOR\n");
}

static void	load_color_C(char **num, t_map *mapi)
{
	mapi->C_color[0] = ft_atoi(num[0]);
	mapi->C_color[1] = ft_atoi(num[1]);
	mapi->C_color[2] = ft_atoi(num[2]);
	if (mapi->C_color[0] < 0 || mapi->C_color[0] > 255)
		printf("ERROR INCORRECT COLOR\n");
	if (mapi->C_color[1] < 0 || mapi->C_color[1] > 255)
		printf("ERROR INCORRECT COLOR\n");
	if (mapi->C_color[2] < 0 || mapi->C_color[2] > 255)
		printf("ERROR INCORRECT COLOR\n");
}

static void	get_colors(char **line, t_map *mapi)
{
	char	**num;
	int		i;

	i = 0;
	num = ft_split(line[1], ',');
	while (num[i])
		i++;
	if (i == 2)
	{
		if (!ft_strcmp(line[0], "F"))
			load_color_F(num, mapi);
		if (!ft_strcmp(line[0], "C"))
			load_color_C(num, mapi);
	}
	else
		printf("ERROR: INCORREC COLOR\n");
	ft_free_dp(num);
}

static void	get_texture_rutes(char **line, t_map *mapi)
{
	if (line != NULL && line[0] != NULL && line[1] != NULL)
	{
		if (!ft_strcmp(line[0], "NO"))
		{
			mapi->NO_rute = ft_strdup(line[1]);
			mapi->have_NO = true;
		}
		else if (!ft_strcmp(line[0], "SO"))
		{
			mapi->SO_rute = ft_strdup(line[1]);
			mapi->have_SO = true;
		}
		else if (!ft_strcmp(line[0], "WE"))
		{
			mapi->WE_rute = ft_strdup(line[1]);
			mapi->have_WE = true;
		}
		else if (!ft_strcmp(line[0], "EA"))
		{
			mapi->EA_rute = ft_strdup(line[1]);
			mapi->have_EA = true;
		}
	}
	else
		printf("ERROR INCORRECT TEXTURE RUTE\n");
}

void	load_map(t_map *mapi, char **map)
{
	int		i;
	char	**line;

	i = 0;
	while (map[i])
	{
		line = ft_split(map[i], ' ');
		get_texture_rutes(line, mapi);
		get_colors(line, mapi);
		ft_free_dp(line);
		i++;
	}
}
