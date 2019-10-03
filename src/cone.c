/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:03:49 by mchett            #+#    #+#             */
/*   Updated: 2019/10/03 15:19:30 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	cone_data(t_mlx *mlx, char **str)
{
	int i;

	i = -1;
	OBJP.pos.x = (double)(ft_atoi(str[1]));
	OBJP.pos.y = (double)(ft_atoi(str[2]));
	OBJP.pos.z = (double)(ft_atoi(str[3]));
	OBJP.r = (double)(ft_atoi(str[4])) / 10;
	OBJP.rot.x = (double)(ft_atoi(str[5])) / 10;
	OBJP.rot.y = (double)(ft_atoi(str[6])) / 10;
	OBJP.rot.z = (double)(ft_atoi(str[7])) / 10;
	if (OBJP.r < 0.1 || ft_atoi(str[8]) < 0 || ft_atoi(str[9]) < 0
		|| ft_atoi(str[10]) < 0)
		ft_error("Wrong input for cone");
	OBJP.col2.r = ft_atoi(str[8]);
	OBJP.col2.g = ft_atoi(str[9]);
	OBJP.col2.b = ft_atoi(str[10]);
	OBJP.specular = (double)(ft_atoi(str[11]));
	OBJP.name = CONE;
	while (++i <= 11)
		free(str[i]);
	free(str);
}

double	cone_intersect(t_vect o, t_vect dir, t_object *obj)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vect	x;

	x = vect_sub(o, obj->pos);
	a = vect_dot(dir, obj->rot);
	a = vect_dot(dir, dir) - (1 + obj->r * obj->r) * a * a;
	b = 2 * (vect_dot(dir, x) - (1 + obj->r * obj->r) *
		vect_dot(dir, obj->rot) * vect_dot(x, obj->rot));
	c = vect_dot(x, x) - (1 + obj->r * obj->r) * pow(vect_dot(x, obj->rot), 2);
	d = b * b - 4 * a * c;
	if (d < EPS)
		return (-1);
	return (get_t(a, b, d));
}

t_vect	cone_normal_calc(t_ray *ray, t_object *obj)
{
	double	m;
	t_vect	n;
	t_vect	p;

	m = obj->t * vect_dot(ray->dir, obj->rot) +
	vect_dot(vect_sub(ray->orig, obj->pos), obj->rot);
	p = vect_sum(ray->orig, vect_scale(ray->dir, obj->t));
	n = vect_scale(vect_scale(obj->rot, m), (1 + obj->r * obj->r));
	n = vect_norm(vect_sub(vect_sub(p, obj->pos), n));
	if (vect_dot(ray->dir, n) > EPS)
		n = vect_scale(n, -1);
	return (n);
}

void	cone(t_mlx *mlx, t_ray *ray, int i, t_object *obj)
{
	obj->t = cone_intersect(ray->orig, ray->dir, obj);
	obj->rot = vect_norm(obj->rot);
	if (obj->t > 0 && obj->t < mlx->min_t)
	{
		mlx->min_t = obj->t;
		mlx->clos_obj = i;
	}
}
