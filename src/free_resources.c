/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:45:09 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/26 18:23:00 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	free_mapi(t_map *mapi)
{
	free(mapi->NO_rute);
	free(mapi->SO_rute);
	free(mapi->WE_rute);
	free(mapi->EA_rute);
	ft_free_dp(mapi->map);
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
