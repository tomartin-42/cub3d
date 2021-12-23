/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 11:30:05 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/23 11:03:00 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "check.h"

//check if have incorrect chars in color line
static void	check_chars_in_color_line(char *color_line, char **map, t_map *mapi)
{
	int	i;

	i = 0;
	while (color_line[i])
	{
		if (color_line[0] == 'C')
		{
			if (!ft_strchr("0123456789,C /t", color_line[i]))
				error_in_color_line(map, mapi);
		}
		else if (color_line[0] == 'F')
		{
			if (!ft_strchr("0123456789,F /t", color_line[i]))
				error_in_color_line(map, mapi);
		}
		i++;
	}
}

//check if have more 2 commas in color line
static void	checking_color_line(char *color_line, char **map, t_map *mapi)
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
		error_in_color_line(map, mapi);
	check_chars_in_color_line(color_line, map, mapi);
}

static void	parse_in_colors(char **map, t_map *mapi)
{
	int		i;
	char	*aux;

	i = 0;
	while (map[i])
	{
		aux = ft_strtrim(map[i], " /t");
		if (aux[0] == 'C')
			checking_color_line(map[i], map, mapi);
		else if (aux[0] == 'F')
			checking_color_line(map[i], map, mapi);
		free(aux);
		i++;
	}			
}

static void	init_redimension_map(t_map *mapi)
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
	parse_in_colors(map, mapi);
	check_chars_in_map(mapi, map);
	init_redimension_map(mapi);
	check_dual_init_point(mapi, map);
	scan_map(mapi, map);
	if (check_close_map(mapi))
		error_open_map(mapi, map);
}
