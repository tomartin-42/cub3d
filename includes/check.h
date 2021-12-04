#ifndef CHECK_H
# define CHECK_H

# include "cube.h"

void	error_in_color_line(char **map, t_map *mapi);
void	error_miss_init_point(char **map, t_map *mapi);
void	error_open_map(t_map *mapi, char **map);
void	error_incorrect_char_in_map(t_map *mapi, char **map);
void	error_empy_map(void);
void	error_dual_init_point(t_map *mapi, char **map);
void	scan_map(t_map *mapi, char **map);
int		check_close_map(t_map *mapi);
void	redimension_map(t_map *mapi, int i, int size_line);
void	check_dual_init_point(t_map *mapi, char **map);
void	check_chars_in_map(t_map *mapi, char **map);

#endif
