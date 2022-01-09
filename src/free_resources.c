/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:45:09 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/27 08:18:00 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	free_mapi(t_map *mapi)
{
	free(mapi->NO_route);
	free(mapi->SO_route);
	free(mapi->WE_route);
	free(mapi->EA_route);
	ft_free_dp(mapi->map);
	free(mapi);
}

void	free_mapi_and_map(t_map *mapi, char **map)
{
	free_mapi(mapi);
	ft_free_dp(map);
}

void	free_ray_and_line(struct s_ray *ray, struct s_line *line)
{
	free(ray);
	free(line);
}
