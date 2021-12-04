#include "check.h"

void	error_in_color_line(void)
{
	ft_putstr_fd("Cube3D error: error in color codificatión.\n", 2);
}

void	error_miss_init_point(void)
{
	ft_putstr_fd("Cube3D error: miss init point.\n", 2);
}

void	error_open_map(void)
{
	ft_putstr_fd("Cube3D error: open map.\n", 2);
}

void	error_empy_map(void)
{
	ft_putstr_fd("Cube3D error: empy map.\n", 2);
	exit (42);
}
