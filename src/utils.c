/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 18:36:54 by tomartin          #+#    #+#             */
/*   Updated: 2021/11/29 11:50:25 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	print_struc_mapi(t_map *mapi)
{
	printf("NO rute: %s\n", mapi->NO_rute);
	printf("SO rute: %s\n", mapi->SO_rute);
	printf("WE rute: %s\n", mapi->WE_rute);
	printf("EA rute: %s\n", mapi->EA_rute);
	printf("F: %ld, %ld, %ld\n", mapi->F_color[0], mapi->F_color[1], mapi->F_color[2]);
	printf("C: %ld, %ld, %ld\n", mapi->C_color[0], mapi->C_color[1], mapi->C_color[2]);
}