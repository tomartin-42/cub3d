/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redimension_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 19:36:07 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/23 11:19:21 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"

void print_table(char **table, int max_x)
{
	int x, y = 0;

	printf("-----\n");
	while (table[y])
	{
		x = 0;
		while (x < max_x)
		{
			printf("%3hhi", table[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("-----\n");
}

static void	copy_old_in_new_map(char **new_map, t_map *mapi)
{
	int	i;
	int	j;
	int	k;
	int	l;

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
	print_struc_mapi(mapi);
}

void	write_x_in_new_map(char **new_map, t_map *mapi)
{
	int	i;
	int	j;

	i = 0;
	while (new_map[i])
	{
		j = 0;
		while (new_map[i][j])
		{
			new_map[i][j] = 'X';
			j++;
		}
		i++;
	}
	copy_old_in_new_map(new_map, mapi);
}

void	redimension_map(t_map *mapi, int i, int size_line)
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
		ft_memset(new_map[i], 'X', size_line);
		new_map[i][size_line - 1] = '\0';
		i--;
	}
	print_table(new_map, size_line);
	copy_old_in_new_map(new_map, mapi);
//	write_x_in_new_map(new_map, mapi);
}
