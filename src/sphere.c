/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:03:20 by mchett            #+#    #+#             */
/*   Updated: 2019/10/02 16:20:43 by mchett           ###   ########.fr       */
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

void	sphere_data(t_mlx *mlx, char **str)
{
	int i;

	i = -1;
	OBJP.pos.x = (double)(atoi(str[1]));
	OBJP.pos.y = (double)(atoi(str[2]));
	OBJP.pos.z = (double)(atoi(str[3]));
	OBJP.r = (double)(atoi(str[4])) / 10;
	if (OBJP.r < 0.1 || atoi(str[5]) < 0 || atoi(str[6]) < 0
		|| atoi(str[7]) < 0)
		ft_error("Wrong input for sphere");
	OBJP.col2.r = atoi(str[5]);
	OBJP.col2.g = atoi(str[6]);
	OBJP.col2.b = atoi(str[7]);
	OBJP.specular = (double)(atoi(str[8]));
	OBJP.name = SPHERE;
	//mlx->obj_counter++;
	while (++i <= 8)
		free(str[i]);
	free(str);
}
