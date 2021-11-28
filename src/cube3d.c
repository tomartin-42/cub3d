/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:46:01 by tomartin          #+#    #+#             */
/*   Updated: 2021/11/28 17:56:42 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int main(int argc, char **argv)
{
	int		fd_map;
	char	**map;

	fd_map = open_map(argc, argv);
	map = read_map(fd_map, argv[1]);
	print_map(map);
}