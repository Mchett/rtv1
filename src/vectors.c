/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:02:31 by mchett            #+#    #+#             */
/*   Updated: 2019/10/03 15:27:45 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vect	vect_norm(t_vect v)
{
	double l;

	l = 1 / vect_len(v);
	return (vect_scale(v, l));
}

t_vect	vect_rot(t_vect d, t_vect r)
{
	d = vect_rotx(d, DTR(r.x));
	d = vect_roty(d, DTR(r.y));
	d = vect_rotz(d, DTR(r.z));
	return (d);
}

t_vect	vect_rotx(t_vect d, double a)
{
	t_vect r;

	r.x = d.x;
	r.y = d.y * cos(a) - d.z * sin(a);
	r.z = d.y * sin(a) + d.z * cos(a);
	return (r);
}

t_vect	vect_roty(t_vect d, double a)
{
	t_vect r;

	r.x = d.x * cos(a) + d.z * sin(a);
	r.y = d.y;
	r.z = d.z * cos(a) - d.x * sin(a);
	return (r);
}

t_vect	vect_rotz(t_vect d, double a)
{
	t_vect	r;

	r.x = d.x * cos(a) - d.y * sin(a);
	r.y = d.x * sin(a) + d.y * cos(a);
	r.z = d.z;
	return (r);
}
