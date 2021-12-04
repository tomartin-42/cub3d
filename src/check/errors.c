#include "check.h"
#include "cube.h"

void	error_in_color_line(char **map, t_map *mapi)
{
	ft_putstr_fd("Cub3D error: error in color codificatión.\n", 2);
	free_mapi_and_map(mapi, map);
	exit (42);
}

void	error_miss_init_point(char **map, t_map *mapi)
{
	ft_putstr_fd("Cub3D error: miss init point.\n", 2);
	free_mapi_and_map(mapi, map);
	exit (42);
}

void	error_open_map(t_map *mapi, char **map)
{
	ft_putstr_fd("Cub3D error: open map.\n", 2);
	free_mapi_and_map(mapi, map);
	exit (42);
}

void	error_empy_map(void)
{
	ft_putstr_fd("Cub3D error: empy map.\n", 2);
	exit (42);
}

void	error_dual_init_point(t_map *mapi, char **map)
{
	ft_putstr_fd("Cub3D error: more than one init point.\n", 2);
	free_mapi_and_map(mapi, map);
	exit (42);
}
