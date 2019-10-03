/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 16:04:58 by mchett            #+#    #+#             */
/*   Updated: 2019/10/03 15:21:34 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	light_data(t_mlx *mlx, char **str)
{
	int i;

	i = -1;
	mlx->light[mlx->light_counter].pos.x = (double)(ft_atoi(str[1]));
	mlx->light[mlx->light_counter].pos.y = (double)(ft_atoi(str[2]));
	mlx->light[mlx->light_counter].pos.z = (double)(ft_atoi(str[3]));
	mlx->light[mlx->light_counter].inten = (double)(ft_atoi(str[4])) / 100;
	if (mlx->light[mlx->light_counter].inten < 0)
		ft_error("Wrong intensity parameter");
	mlx->light_counter++;
	while (++i <= 4)
		free(str[i]);
	free(str);
}

int		shadow_init(t_light *light, t_mlx *mlx)
{
	int		i;
	double	max_t;
	double	t;
	t_vect	dir;

	i = -1;
	t = 0;
	max_t = vect_len(vect_sub(light->pos, light->p));
	dir = vect_norm(vect_sub(light->pos, light->p));
	light->p = vect_sum(light->p, vect_scale(dir, EPS));
	while (++i < mlx->obj_num)
	{
		if (mlx->obj[i].name == SPHERE)
			t = sphere_intersect(light->p, dir, &mlx->obj[i]);
		else if (mlx->obj[i].name == PLANE)
			t = plane_intersect(light->p, dir, &mlx->obj[i]);
		else if (mlx->obj[i].name == CONE)
			t = cone_intersect(light->p, dir, &mlx->obj[i]);
		else if (mlx->obj[i].name == CYLINDER)
			t = cylinder_intersect(light->p, dir, &mlx->obj[i]);
		if (t > 0.00001 && t < max_t)
			return (1);
	}
	return (0);
}

void	get_intensity(t_mlx *mlx, t_light *light, t_vect v, double s)
{
	double	n_dot_l;
	double	r_dot_v;
	double	inten;
	t_vect	l;
	t_vect	r;

	light->new_inten = mlx->ambient;
	inten = 0.0;
	l = vect_norm(vect_sub(light->pos, light->p));
	n_dot_l = vect_dot(light->n, l);
	if (shadow_init(light, mlx) == 0)
		inten = light->inten;
	if (n_dot_l > EPS)
		light->new_inten += inten * (n_dot_l / (vect_len(light->n) *
					vect_len(l)));
	if (s > 0)
	{
		r = vect_scale(light->n, 2);
		r = vect_scale(r, vect_dot(light->n, l));
		r = vect_sub(r, l);
		r_dot_v = vect_dot(r, v);
		if (r_dot_v > EPS)
			light->new_inten += inten * pow((r_dot_v / (vect_len(r) *
							vect_len(v))), s);
	}
}

void	light(t_mlx *mlx, t_ray *ray)
{
	int	i;

	i = 0;
	if (mlx->clos_obj > -1)
	{
		while (i < mlx->light_num)
		{
			mlx->light[i].p = vect_sum(ray->orig, vect_scale(ray->dir, OBJ.t));
			if (OBJ.name == SPHERE)
				mlx->light[i].n = sphere_normal(ray, &OBJ);
			else if (OBJ.name == PLANE)
				mlx->light[i].n = OBJ.rot;
			else if (OBJ.name == CYLINDER)
				mlx->light[i].n = cyl_normal_calc(ray, &OBJ);
			else if (OBJ.name == CONE)
				mlx->light[i].n = cone_normal_calc(ray, &OBJ);
			get_intensity(mlx, &mlx->light[i], vect_scale(ray->dir, -1),
					OBJ.specular);
			i++;
		}
	}
}
