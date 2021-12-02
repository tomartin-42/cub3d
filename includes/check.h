#ifndef CHECK_H
# define CHECK_H

# include "cube.h"

void	error_in_color_line(void);
void	error_miss_init_point(void);
void	error_open_map(void);
void	scan_map(t_map *map);
int		check_close_map(t_map *mapi);

#endif
