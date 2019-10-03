/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 16:32:52 by mchett            #+#    #+#             */
/*   Updated: 2019/10/03 12:11:28 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int color(t_rgb rgb)
{
	//printf("r = %d, g = %d, b = %d\n",rgb.r,rgb.g ,rgb.b);
	//printf("%d\n",rgb.r << 16| rgb.g << 8 | rgb.b);
	return ((rgb.r << 16| rgb.g << 8 | rgb.b));;
}

void	set_color(t_mlx *mlx, int i, int x, int y)
{
	double	p;
	int		k;

	k = 0;
	p = 0;
	while (k < mlx->light_num)
	{
		if (mlx->light[k].new_inten > 1)
			mlx->light[k].new_inten = 1;
		p += mlx->light[k].new_inten;
		if (p > 1)
			p = 1;
		k++;
	}
	if (i > -1)
	{
		int k = color(mlx->obj[i].col2);
		if(k != 0)
			//printf("%d\n",k);
		image_set_pixel(mlx->image, x, y, k);
	}
	else
		image_set_pixel(mlx->image, x, y, 0);
}

void	get_dir(double x, double y, t_ray *ray, t_mlx *mlx)
{
	ray->dir.x = x * (V_W / (double)W_W);
	ray->dir.y = y * (V_H / (double)W_H);
	ray->dir.z = 1.0;
	ray->dir = vect_rot(ray->dir, mlx->cam.rot);
}

void	intersection_check(t_ray *ray, t_mlx *mlx, int x, int y)
{
	int	i;

	i = 0;
	mlx->clos_obj = -1;
	mlx->min_t = INFINITY;
	while (i < mlx->obj_num)
	{
		if (mlx->obj[i].name == SPHERE)
			sphere(mlx, ray, i, &mlx->obj[i]);
		else if (mlx->obj[i].name == PLANE)
			plane(mlx, ray, i, &mlx->obj[i]);
		else if (mlx->obj[i].name == CYLINDER)
			cylinder(mlx, ray, i, &mlx->obj[i]);
		else if (mlx->obj[i].name == CONE)
			cone(mlx, ray, i, &mlx->obj[i]);
		i++;
	}
	if (mlx->clos_obj > -1)
		light(mlx, ray);
	set_color(mlx, mlx->clos_obj, x, y);
}

void	ray_trace_init(t_mlx *mlx, t_ray *ray)
{
	int		x;
	int		y;
	double	n_x;
	double	n_y;

	x = 0;
	while (x <= W_W)
	{
		y = 0;
		n_x = (x + 0.5) / (double)W_W;
		n_x = 2 * n_x - 1;
		while (y <= W_H)
		{
			n_y = (y + 0.5) / (double)W_H;
			n_y = 1 - (2 * n_y);
			get_dir(n_x, n_y, ray, mlx);
			intersection_check(ray, mlx, x, y);
			y++;
		}
		x++;
	}
}