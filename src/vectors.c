/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:02:31 by mchett            #+#    #+#             */
/*   Updated: 2019/10/02 15:59:12 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vect	*new_vect(t_vect *e, t_vect *s)
{
	t_vect *v;

	v = (t_vect*)ft_memalloc(sizeof(t_vect));
	if (v == NULL)
		return (v);
	v->x = e->x - s->x;
	v->y = e->y - s->y;
	v->z = e->z - s->z;
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
	a->x += b->x;
	a->y += b->y;
	a->z += b->z;
	return (a);
}

t_vect	*vect_sub(t_vect *a, t_vect *b)
{
	a->x -= b->x;
	a->y -= b->y;
	a->z -= b->z;
	return (a);
}

t_vect	*vect_scale(t_vect *v, double b)
{
	v->x *= b;
	v->y *= b;
	v->z *= b;
	return (v);
}

double	vect_proizv(t_vect *v, t_vect *b)
{
	return (v->x * b->x + v->y * b->y + v->z * b->z);
}

double	vect_len(t_vect *v)
{
	return (sqrt(vect_proizv(v, v)));
}

t_vect	*vect_norm(t_vect *v)
{
	double l;

	l = 1 / vect_len(v);
	return (vect_scale(v, l));
}

t_vect	*vect_rot(t_vect *d, t_vect *r)
{
	d = vect_rotx(d, DTR(r->x));
	d = vect_roty(d, DTR(r->y));
	d = vect_rotz(d, DTR(r->z));
	return (d);
}

t_vect	*vect_rotx(t_vect *d, double a)
{
	t_vect *r;

	r = (t_vect*)ft_memalloc(sizeof(t_vect));
	if (r == NULL)
		return (r);
	r->x = d->x;
	r->y = d->y * cos(a) - d->z * sin(a);
	r->z = d->y * sin(a) + d->z * cos(a);
	return (r);
}

t_vect	*vect_roty(t_vect *d, double a)
{
	t_vect *r;

	r = (t_vect*)ft_memalloc(sizeof(t_vect));
	if (r == NULL)
		return (r);
	r->x = d->x * cos(a) + d->z * sin(a);
	r->y = d->y;
	r->z = d->z * cos(a) - d->x * sin(a);
	return (r);
}

t_vect	*vect_rotz(t_vect *d, double a)
{
	t_vect	*r;

	r = (t_vect*)ft_memalloc(sizeof(t_vect));
	if (r == NULL)
		return (r);
	r->x = d->x * cos(a) - d->y * sin(a);
	r->y = d->x * sin(a) + d->y * cos(a);
	r->z = d->z;
	return (r);
}
