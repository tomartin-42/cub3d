/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:51:55 by tomartin          #+#    #+#             */
/*   Updated: 2021/11/29 10:39:49 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

//check if the file have .cub extension
static void	check_cub(char *argv)
{
	char	*point;

	point = ft_strnstr(argv, ".cub", ft_strlen(argv));
	if (point == NULL)
	{
		ft_putstr_fd("error: incorrect extension\n", 2);
		exit (1);
	}
	if (*point != '.' || *(point + 1) != 'c' || *(point + 2) != 'u'
		|| *(point + 3) != 'b' || *(point + 4) != '\0')
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

//copy the file content in a dp and return it
static char	**save_map(char *argv, int i)
{
	char	**map;
	int		fd;
	char	*line;

	map = (char **) malloc(sizeof(char *) * (i + 1));
	map[i] = NULL;
	i = 0;
	fd = open(argv, O_RDONLY);
	while (get_next_line(fd, &line))
	{
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
	close(fd_map);
	map = save_map(argv, i);
	return (map);
}
