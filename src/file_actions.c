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

/* Returns an allocated pointer containing the map in 
 * an array of char * . */
static char	**save_map(char *argv, int line_number)
{
	char	**map;
	int		fd;
	char	*line;

	map = (char **) malloc(sizeof(char *) * (line_number + 1));
	map[line_number] = NULL;
	line_number = 0;
	fd = open(argv, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		map[line_number] = ft_strdup(line);
		free(line);
		++line_number;
	}
    map[line_number] = ft_strdup(line);
    free(line);
	close (fd);
	return (map);
}

char	**read_map(int fd_map, char *argv)
{
	int		line_counter;
	char	*line;
	char	**map;

    line_counter = 0;
    line = NULL;
    while (get_next_line(fd_map, &line) != 0)
    {
        free(line);
        line = NULL;
        ++line_counter;
    }
    free(line);
    ++line_counter;
	printf("numero lineas mapa %i\n", line_counter);
	close(fd_map);
	if (line_counter == 0)
		error_empty_map();
	map = save_map(argv, line_counter);
	return (map);
}
