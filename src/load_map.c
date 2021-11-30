/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 08:53:28 by tomartin          #+#    #+#             */
/*   Updated: 2021/11/30 09:07:59 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	load_color_F(char **num, t_map *mapi)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (num[i])
	{
		if (ft_strlen(num[i]))
		{
			mapi->F_color[j] = ft_atoi(num[i]);
			if (mapi->F_color[j] < 0 || mapi->F_color[0] > 255)
				printf("ERROR INCORRECT COLOR\n");
			j++;
		}
		i++;
	}
	mapi->have_F = true;
}

static void	load_color_C(char **num, t_map *mapi)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (num[i])
	{
		if (ft_strlen(num[i]))
		{
			mapi->C_color[j] = ft_atoi(num[i]);
			if (mapi->C_color[j] < 0 || mapi->C_color[0] > 255)
				printf("ERROR INCORRECT COLOR\n");
			j++;
		}
		i++;
	}
	mapi->have_F = true;
}

static void	get_colors(char **line, t_map *mapi, char *c_line)
{
	char	**num;
	char	*aux;
	int		i;

	i = 0;
	num = ft_split(c_line, ',');
	while (num[i])
	{
		aux = ft_strtrim(num[i], " ,CF");
		free(num[i]);
		num[i] = ft_strdup(aux);
		free(aux);
		i++;
	}
	if (!ft_strcmp(line[0], "F"))
		load_color_F(num, mapi);
	if (!ft_strcmp(line[0], "C"))
		load_color_C(num, mapi);
	ft_free_dp(num);
}

//
static void	get_texture_and_colors(char **line, t_map *mapi, char *c_line)
{
	if (line != NULL && line[0] != NULL && line[1] != NULL)
	{
		if (!ft_strcmp(line[0], "NO") && mapi->have_NO == false)
		{
			mapi->NO_rute = ft_strdup(line[1]);
			mapi->have_NO = true;
		}
		else if (!ft_strcmp(line[0], "SO") && mapi->have_SO == false)
		{
			mapi->SO_rute = ft_strdup(line[1]);
			mapi->have_SO = true;
		}
		else if (!ft_strcmp(line[0], "WE") && mapi->have_WE == false)
		{
			mapi->WE_rute = ft_strdup(line[1]);
			mapi->have_WE = true;
		}
		else if (!ft_strcmp(line[0], "EA") && mapi->have_EA == false)
		{
			mapi->EA_rute = ft_strdup(line[1]);
			mapi->have_EA = true;
		}
		else if (!ft_strcmp(line[0], "F") && mapi->have_F == false)
			get_colors(line, mapi, c_line);
		else if (!ft_strcmp(line[0], "C") && mapi->have_C == false)
			get_colors(line, mapi, c_line);
	}
}

// check if all the parameters have been loaded into the mapi structure
// otherwise it continues to loop. It is necessary to
// know when start map matrix
static int	check_param_map(t_map *mapi)
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
	if (mapi->F_color[0] == EMPY || mapi->F_color[1] == EMPY
		|| mapi->F_color[2] == EMPY)
		ret = 1;
	if (mapi->C_color[0] == EMPY || mapi->C_color[1] == EMPY
		|| mapi->C_color[2] == EMPY)
		ret = 1;
	return (ret);
}

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
	printf("[[%d]]\n", i);
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
		get_texture_and_colors(line, mapi, map[i]);
		ft_free_dp(line);
		i++;
		if (!check_param_map(mapi))
			break ;
	}
	if (check_param_map(mapi))
		printf("ERROR: MISS PARAM IN FILE\n");
	else
		get_map(i, mapi, map);
}
