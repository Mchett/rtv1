/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:15:43 by mchett            #+#    #+#             */
/*   Updated: 2019/10/04 16:46:42 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_mlx		*mlxdel(t_mlx *mlx)
{
	if (mlx->win_ptr != NULL)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	ft_memdel((void **)&mlx);
	return (NULL);
}

void		init_buf(t_object ***ob_buf, t_light ***lt_buf, t_mlx *mlx)
{
	int		j;
	int		i;

	i = -1;
	*ob_buf = (t_object **)ft_memalloc(sizeof(t_object *) * THREADS);
	*lt_buf = (t_light **)ft_memalloc(sizeof(t_light *) * THREADS);
	while (++i < THREADS)
	{
		(*ob_buf)[i] = (t_object *)ft_memalloc(sizeof(t_object) * mlx->obj_num);
		(*lt_buf)[i] = (t_light *)ft_memalloc(sizeof(t_object) *
			mlx->light_num);
		j = -1;
		while (++j < mlx->obj_num)
			(*ob_buf)[i][j] = mlx->obj[j];
		j = -1;
		while (++j < mlx->light_num)
			(*lt_buf)[i][j] = mlx->light[j];
	}
}

t_mlx		*ft_init(char *str, void *ini)
{
	t_mlx	*mlx;

	if ((mlx = ft_memalloc(sizeof(t_mlx))) == NULL || ini == NULL)
		ft_error("Error malloc in ft_init()");
	mlx->mlx_ptr = ini;
	if ((mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, W_W,
										W_H, str)) == NULL ||
			(mlx->image = new_image(mlx)) == NULL ||
			(mlx->mouse = ft_memalloc(sizeof(t_mouse))) == NULL)
	{
		mlxdel(mlx);
		ft_error("Error malloc in ft_init()");
	}
	mlx->obj_num = 0;
	mlx->light_num = 0;
	mlx->obj_counter = 0;
	mlx->light_counter = 0;
	mlx->mouse->x = 0;
	mlx->mouse->y = 0;
	mlx->mouse->right = 0;
	return (mlx);
}

void		copy(t_mlx *mlx, t_mlx m[THREADS])
{
	int			i;
	t_object	**ob_buf;
	t_light		**lt_buf;

	ob_buf = mlx->ob_buf;
	lt_buf = mlx->lt_buf;
	i = -1;
	while (++i < THREADS)
	{
		m[i] = *mlx;
		m[i].obj = ob_buf[i];
		m[i].light = lt_buf[i];
	}
}
