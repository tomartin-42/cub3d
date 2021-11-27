/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:51:55 by tomartin          #+#    #+#             */
/*   Updated: 2021/11/27 16:26:21 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

//check if the file have .cub extension
static void	check_cub(char *argv)
{
	char *point;

	point = ft_strnstr(argv, ".cub", ft_strlen(argv));
	if (point == NULL)
	{
		ft_putstr_fd("error: incorrect extension\n", 2);
		exit (1);
	}
	if (*point != '.' || *(point + 1) != 'c' || *(point + 2) != 'u' || *(point + 3) != 'b'
		|| *(point + 4) != '\0')
	{
		ft_putstr_fd("error: incorrect extension", 2);
		exit (1);
	}
}

int	open_map(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		ft_putstr_fd("error: bad number of arguments\n", 2);
		exit(1);
	}
	check_cub(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{	
		ft_putstr_fd("error: cannot open file map\n", 2);
		exit(1);
	}
	return (fd);
}