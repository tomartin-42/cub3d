/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:51:55 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/23 10:45:20 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "check.h"

static void print_incorrect_extension_error(void)
{
	ft_putstr_fd("Cub3D error: incorrect extension\n", 2);
	exit(1);
}

/* Checks wether the file has a .cub extension. */
static void	check_cub(char *argv)
{
	char	*point;
	char	*last;

	last = NULL;
	point = ft_strnstr(argv, ".cub", ft_strlen(argv));
	if (!point)
		print_incorrect_extension_error();
	else
	{
		while (point)
		{
			last = point;
			point = ft_strnstr(point + 4, ".cub", ft_strlen(point + 4));
		}
	}
	if (*(last + 4) != '\0')
		print_incorrect_extension_error();
}

int	open_map(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		ft_putstr_fd("Cub3D error: bad number of arguments\n", 2);
		exit(1);
	}
	check_cub(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 1)
	{	
		ft_putstr_fd("Cub3D error: cannot open file map\n", 2);
		exit(1);
	}
	return (fd);
}

//copy the file content in a dp and return it
static char	**save_map(char *argv, int i)
{
	char	**map;
	int		fd;
	char	*line;
	int		control;

	control = 1;
	map = (char **) malloc(sizeof(char *) * (i + 2));
	map[i + 1] = NULL;
	i = 0;
	fd = open(argv, O_RDONLY);
	while (control)
	{
		control = get_next_line(fd, &line);
		map[i] = ft_strdup(line);
		free(line);
		i++;
	}
	close (fd);
	return (map);
}

char	**read_map(int fd_map, char *argv)
{
	int		i;
	char	end_line;
	char	**map;

	i = 0;
	while (read(fd_map, &end_line, 1))
	{
		if (end_line == '\n')
			i++;
	}
	printf("numero lineas mapa %i\n", i);
	close(fd_map);
	if (i == 0)
		error_empty_map();
	map = save_map(argv, i);
	return (map);
}
