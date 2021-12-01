/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 11:30:05 by tomartin          #+#    #+#             */
/*   Updated: 2021/11/30 11:35:50 by tomartin         ###   ########.fr       */
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

//check if have more 3 commas in color line
static void checking_color_line(char *color_line)
{
	int commas;
	int i;

	i = 0;
	commas = 0;
	while (color_line[i])
	{
		if (color_line[i] == ',')
			commas++;
		i++;
	}
	if (commas != 3)
		error_in_color_line();
	check_chars_in_color_line(color_line);
}


static void parse_in_colors(char **map)
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

void	main_check(t_map *mapi, char **map)
{
	parse_in_colors(map);
	(void)mapi;
	(void)map;
}
