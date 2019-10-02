/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:03:20 by mchett            #+#    #+#             */
/*   Updated: 2019/10/02 13:38:23 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_sphere *new_sphere(double r, t_vect *p)
{
	t_sphere	*s;

	s = (t_sphere*)ft_memalloc(sizeof(t_sphere));
	if (s == NULL)
		return (s);
	s->centr = p;
	s->r = r;
	return (s); 
}

int ray_intersect(t_vect *orig, t_vect *dir,t_sphere *s)
{
	double	tca;
	double	d2;
	double	t0;
	double	t1;
	t_vect *L = new_vect(s->centr, orig);

	tca = vect_proizv(L, dir);
	d2 = vect_proizv(L, L) - tca * tca;
	if (d2 > s->r * s->r) 
	{
		return (0);
	}
	t0 = tca - sqrt(s->r * s->r - d2);
	t1 = tca + sqrt(s->r * s->r - d2);
	if (t0 < 0 && t1 < 0 )
	{
		return (0);
	}
	return (1);
}