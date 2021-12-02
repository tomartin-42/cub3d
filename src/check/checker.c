/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 11:30:05 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/02 13:49:42 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "check.h"

//check if have incorrect chars in color line
static void	check_chars_in_color_line(char *color_line)
{
	int	i;

	i = 0;
	while (color_line[i])
	{
		if (color_line[0] == 'C')
		{
			if (!ft_strchr("0123456789,C /t", color_line[i]))
			{		
				error_in_color_line();
				break ;
			}
		}
		else if (color_line[0] == 'F')
		{
			if (!ft_strchr("0123456789,F /t", color_line[i]))
			{		
				error_in_color_line();
				break ;
			}
		}
		i++;
	}
}

//check if have more 2 commas in color line
static void	checking_color_line(char *color_line)
{
	int	commas;
	int	i;

	i = 0;
	commas = 0;
	while (color_line[i])
	{
		if (color_line[i] == ',')
			commas++;
		i++;
	}
	if (commas != 2)
		error_in_color_line();
	check_chars_in_color_line(color_line);
}

static void	parse_in_colors(char **map)
{
	int		i;
	char	*aux;

	i = 0;
	while (map[i])
	{
		aux = ft_strtrim(map[i], " /t");
		if (aux[0] == 'C')
			checking_color_line(map[i]);
		else if (aux[0] == 'F')
			checking_color_line(map[i]);
		free(aux);
		i++;
	}			
}

static void	copy_old_in_new_map(char **new_map, t_map *mapi)
{
	int i;
	int j;
	int k;
	int l;

	i = 0;
	k = 1;
	while (mapi->map[i])
	{
		j = 0;
		l = 1;
		while (mapi->map[i][j] != '\0')
		{
			if (mapi->map[i][j] != ' ')
				new_map[k][l] = mapi->map[i][j];
			j++;
			l++;
		}
		i++;
		k++;
	}
	ft_free_dp(mapi->map);
	mapi->map = new_map;
}

static void	write_x_in_new_map(char **new_map, t_map *mapi)
{
	int	i;
	int	j;

	i = 0;
	while(new_map[i])
	{
		j = 0;
		while(new_map[i][j])
		{	
			new_map[i][j] = 'X';
			j++;
		}
		i++;
	}
	copy_old_in_new_map(new_map, mapi);
}

static void	redimension_map(t_map *mapi, int i, int size_line)
{
	char	**new_map;

	i = i + 3;
	size_line = size_line + 3;
	new_map = (char **) malloc(sizeof(char *) * i);
	new_map[i - 1] = NULL;
	i = i - 2;
	while (i >= 0)
	{
		new_map[i] = (char *) malloc(sizeof(char) * size_line);
		new_map[i][size_line - 1] = '\0';
		i--;
	}
	write_x_in_new_map(new_map, mapi);
}

static void	parse_in_map(t_map *mapi)
{
	int	size_line;
	int	i;

	i = 0;
	size_line = 0;
	while (mapi->map[i])
	{
		if (ft_strlen(mapi->map[i]) > (size_t)size_line)
			size_line = ft_strlen(mapi->map[i]);
		i++;
	}
	redimension_map(mapi, i, size_line);
}

void	main_check(t_map *mapi, char **map)
{
	parse_in_colors(map);
	parse_in_map(mapi);
	scan_map(mapi);
	(void)mapi;
	(void)map;
}
