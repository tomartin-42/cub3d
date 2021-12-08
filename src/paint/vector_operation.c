/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 10:52:03 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/08 19:20:02 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paint.h"

t_vect	sum_v(t_vect v_a, t_vect v_b)
{
	t_vect	answ;

	answ.o.x = v_a.o.x + v_b.o.x;
	answ.o.y = v_a.o.y + v_b.o.y;
	return (answ);
}

t_vect	subtr_v(t_vect v_a, t_vect v_b)
{
	t_vect	answ;

	answ.o.x = v_a.o.x - v_b.o.x;
	answ.o.y = v_a.o.y - v_b.o.y;
	return (answ);
}

double	mod_v(t_vect vect)
{
	double	answ;

	answ = sqrtf(powf(vect.o.x, 2) + powf(vect.o.y, 2));
	return (answ);
}

t_vect	proc_vect(t_vect v_a, double n)
{
	t_vect	answ;

	answ.o.x = v_a.o.x * n;
	answ.o.y = v_a.o.y * n;
	return (answ);
}

void	load_values_v(t_vect *load, double x, double y)
{
	load->o.x = x;
	load->o.y = y;
}
