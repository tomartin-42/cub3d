#include "check.h"

static void	set_init_point(t_map *mapi, int x, int y)
{
	mapi->init_point = mapi->map[x][y];
	mapi->xy_init_point[0] = y;
	mapi->xy_init_point[1] = x;
}

int	check_close_map(t_map *mapi)
{
	int	i;
	int j;
	bool open_map;

	open_map = false;
	i = 0;
	while (mapi->map[i])
	{
		j = 0;
		while (mapi->map[i][j])
		{
			if (mapi->map[i][j] == '0')
			{
				if (mapi->map[i - 1][j] == 'X' || mapi->map[i + 1][j] == 'X'
					|| mapi->map[i][j - 1] == 'X'
					|| mapi->map[i][j + 1] == 'X')
					open_map = true;
			}
			j++;
		}
		i++;
	}
	return (open_map);
}


void	scan_map(t_map *mapi)
{
	int		i;
	int		j;
	bool	start_point;

	i = 0;
	start_point = false;
	while (mapi->map[i] && start_point == false)
	{
		j = 0;
		while (mapi->map[i][j] && start_point == false)
		{
			if (ft_strchr("NSWE", mapi->map[i][j]))
			{
				set_init_point(mapi, i, j);
				start_point = true;
			}
			j++;
		}
		i++;
	}
	if (start_point == false)
		error_miss_init_point();
}
