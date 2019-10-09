/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanfred <cmanfred@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:03:41 by mchett            #+#    #+#             */
/*   Updated: 2019/10/05 14:32:11 by cmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	cylinder_data(t_mlx *mlx, char **str)
{
	int i;

	i = -1;
	if (ft_check_len(str) != 12)
		ft_error("Wrong input");
	OBJP.pos.x = (double)(ft_atoi(str[1]));
	OBJP.pos.y = (double)(ft_atoi(str[2]));
	OBJP.pos.z = (double)(ft_atoi(str[3]));
	OBJP.r = (double)(ft_atoi(str[4])) / 10;
	OBJP.rot.x = (double)(ft_atoi(str[5]));
	OBJP.rot.y = (double)(ft_atoi(str[6]));
	OBJP.rot.z = (double)(ft_atoi(str[7]));
	if (OBJP.r < 0.1 || ft_atoi(str[8]) < 0 || ft_atoi(str[9]) < 0
		|| ft_atoi(str[10]) < 0)
		ft_error("Wrong input for cylinder");
	OBJP.col.r = ft_atoi(str[8]);
	OBJP.col.g = ft_atoi(str[9]);
	OBJP.col.b = ft_atoi(str[10]);
	OBJP.specular = (double)(ft_atoi(str[11]));
	OBJP.name = CYLINDER;
	mlx->obj_counter++;
}

double	cylinder_intersect(t_vect o, t_vect dir, t_object *obj)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vect	x;

	x = vect_sub(o, obj->pos);
	a = vect_dot(dir, dir) - pow(vect_dot(dir, obj->rot), 2);
	b = 2 * (vect_dot(dir, x) - (vect_dot(dir, obj->rot) *
	vect_dot(x, obj->rot)));
	c = vect_dot(x, x) - pow(vect_dot(x, obj->rot), 2) - pow(obj->r, 2);
	d = b * b - 4 * a * c;
	if (d < 0)
		return (-1);
	return (get_t(a, b, d));
}

t_vect	cyl_normal_calc(t_ray *ray, t_object *obj)
{
	double	m;
	t_vect	n;
	t_vect	p;

	m = obj->t * vect_dot(ray->dir, obj->rot) +
	vect_dot(vect_sub(ray->orig, obj->pos), obj->rot);
	p = vect_sum(ray->orig, vect_scale(ray->dir, obj->t));
	n = vect_norm(vect_sub(vect_sub(p, obj->pos), vect_scale(obj->rot, m)));
	if (vect_dot(ray->dir, n) > EPS)
		n = vect_scale(n, -1);
	return (n);
}

void	cylinder(t_mlx *mlx, t_ray *ray, int i, t_object *obj)
{
	obj->t = cylinder_intersect(ray->orig, ray->dir, obj);
	obj->rot = vect_norm(obj->rot);
	if (obj->t > 0 && obj->t < mlx->min_t)
	{
		mlx->min_t = obj->t;
		mlx->clos_obj = i;
	}
}
