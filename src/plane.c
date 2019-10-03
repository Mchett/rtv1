/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:04:02 by mchett            #+#    #+#             */
/*   Updated: 2019/10/03 15:26:01 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	plane_data(t_mlx *mlx, char **str)
{
	int i;

	i = -1;
	OBJP.pos.x = (double)(ft_atoi(str[1]));
	OBJP.pos.y = (double)(ft_atoi(str[2]));
	OBJP.pos.z = (double)(ft_atoi(str[3]));
	OBJP.rot.x = (double)(ft_atoi(str[4]));
	OBJP.rot.y = (double)(ft_atoi(str[5]));
	OBJP.rot.z = (double)(ft_atoi(str[6]));
	if (ft_atoi(str[7]) < 0 || ft_atoi(str[8]) < 0 || ft_atoi(str[9]) < 0)
		ft_error("Wrong input");
	OBJP.col2.r = ft_atoi(str[7]);
	OBJP.col2.g = ft_atoi(str[8]);
	OBJP.col2.b = ft_atoi(str[9]);
	OBJP.specular = (double)(ft_atoi(str[10]));
	OBJP.name = PLANE;
	mlx->obj_counter++;
	while (++i <= 10)
		free(str[i]);
	free(str);
}

double	plane_intersect(t_vect o, t_vect dir, t_object *obj)
{
	double	t;
	double	a;
	double	b;
	t_vect	x;

	x = vect_sub(o, obj->pos);
	a = vect_dot(x, obj->rot);
	b = vect_dot(dir, obj->rot);
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
		return (-1);
	t = -a / b;
	if (t > EPS)
		return (t);
	return (-1);
}

void	plane(t_mlx *mlx, t_ray *ray, int i, t_object *obj)
{
	obj->rot = vect_norm(obj->rot);
	obj->t = plane_intersect(ray->orig, ray->dir, obj);
	if (obj->t > 0 && obj->t < mlx->min_t)
	{
		mlx->min_t = obj->t;
		mlx->clos_obj = i;
	}
}
