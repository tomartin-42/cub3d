/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:36:43 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/14 12:14:29 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paint.h"

int	transform_color(long int color[3])
{
	int	color_resp;

	color_resp = ((color[0] << 16) | (color[1] << 8) | color[2]);
	return (color_resp);
}
