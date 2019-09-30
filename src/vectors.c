/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:02:31 by mchett            #+#    #+#             */
/*   Updated: 2019/09/30 17:24:42 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

double	vect_len(t_vect *v)
{
	return (sqrt(v->x*v->x + v->y * v->y + v->z * v->z)); 
}

t_vect	*new_vect(t_vect *e, t_vect *s)
{
	t_vect *v;

	v = (t_vect*)ft_memalloc(sizeof(t_vect));
	if (v == NULL)
		return (v);
	v->x = - s->x + e->x;
	v->y = - s->y + e->y;
	v->z = - s->z + e->z;
	return (v); 
}

t_vect	*new_vect2(double x, double y, double z)
{
	t_vect *v;

	v = (t_vect*)ft_memalloc(sizeof(t_vect));
	if (v == NULL)
		return (v);
	v->x = x;
	v->y = y;
	v->z = z;
	return (v); 
}

t_vect	*vect_sum(t_vect *a, t_vect *b)
{
	t_vect *v;

	v = (t_vect*)ft_memalloc(sizeof(t_vect));
	if (v == NULL)
		return (v);
	v->x = a->x + b->x;
	v->y = a->y + b->y;
	v->z = a->z + b->z;
	return (v); 
}

t_vect	*vect_minus(t_vect *a, t_vect *b)
{
	t_vect *v;

	v = (t_vect*)ft_memalloc(sizeof(t_vect));
	if (v == NULL)
		return (v);
	v->x = a->x - b->x;
	v->y = a->y - b->y;
	v->z = a->z - b->z;
	return (v); 
}

t_vect	*vect_proizv(t_vect *v, double b)
{
	v->x *= b;
	v->y *= b;
	v->z *= b;
	return (v); 
}

double	vect_proizv_v(t_vect *v, t_vect *b)
{
	return (v->x * b->x + v->y * b->y +	v->z * b->z); 
}

t_vect	*vect_norm(t_vect *v)
{
	double l;

	l = vect_len(v);
	v->x /= l;
	v->y /= l;
	v->z /= l;
	return (v); 
}




