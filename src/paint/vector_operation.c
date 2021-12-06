/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 10:52:03 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/06 11:26:30 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paint.h"

t_vect	sum_v(t_vect v_a, t_vect v_b)
{
	t_vect	answ;

	answ.o.x = v_a.o.x + v_b.o.x;
	answ.o.y = v_a.o.y + v_b.o.y;
	answ.f.x = v_a.f.x + v_b.f.x;
	answ.f.y = v_a.f.y + v_b.f.y;
	return (answ);
}

t_vect	subtr_v(t_vect v_a, t_vect v_b)
{
	t_vect	answ;

	answ.o.x = v_a.o.x - v_b.o.x;
	answ.o.y = v_a.o.y - v_b.o.y;
	answ.f.x = v_a.f.x - v_b.f.x;
	answ.f.y = v_a.f.y - v_b.f.y;
	return (answ);
}

float	mod_v(t_vect vect)
{
	float	answ;
	float	a;
	float	b;

	a = vect.f.x - vect.o.x;
	b = vect.f.y - vect.o.y;
	answ = sqrtf(powf(a, 2) + powf(b, 2));
	return (answ);
}
