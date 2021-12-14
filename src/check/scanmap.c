/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:44:15 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/14 10:45:35 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"

static void	set_init_point(t_map *mapi, int x, int y)
{
	mapi->init_point = mapi->map[x][y];
	mapi->xy_init_point[0] = y;
	mapi->xy_init_point[1] = x;
}

int	check_close_map(t_map *mapi)
{
	int		i;
	int		j;
	bool	open_map;

	open_map = false;
	i = 0;
	while (mapi->map[i])
	{
		j = 0;
		while (mapi->map[i][j])
		{
			if (mapi->map[i][j] == '0')
			{
				if (mapi->map[i - 1][j] == 'X' || mapi->map[i + 1][j] == 'X'
					|| mapi->map[i][j - 1] == 'X'
					|| mapi->map[i][j + 1] == 'X')
					open_map = true;
			}
			j++;
		}
		i++;
	}
	return (open_map);
}

//Get coordinates of the starting point
void	scan_map(t_map *mapi, char **map)
{
	int		i;
	int		j;
	bool	start_point;

	i = 0;
	start_point = false;
	while (mapi->map[i] && start_point == false)
	{
		j = 0;
		while (mapi->map[i][j] && start_point == false)
		{
			if (ft_strchr("NSWE", mapi->map[i][j]))
			{
				set_init_point(mapi, i, j);
				start_point = true;
			}
			j++;
		}
		i++;
	}
	if (start_point == false)
		error_miss_init_point(map, mapi);
}

void	check_dual_init_point(t_map *mapi, char **map)
{
	int	init_p;
	int	i;
	int	j;

	i = 0;
	init_p = 0;
	while (mapi->map[i])
	{
		j = 0;
		while (mapi->map[i][j])
		{
			if (ft_strchr("NSWE", mapi->map[i][j]))
				init_p++;
			j++;
		}
		i++;
	}
	if (init_p != 1)
		error_dual_init_point(mapi, map);
}

void	check_chars_in_map(t_map *mapi, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (mapi->map[i])
	{
		j = 0;
		while (mapi->map[i][j])
		{
			if (!ft_strchr(" /t10NSWE", mapi->map[i][j]))
				error_incorrect_char_in_map(mapi, map);
			j++;
		}
		i++;
	}
}
