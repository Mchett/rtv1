/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:15:43 by mchett            #+#    #+#             */
/*   Updated: 2019/10/02 14:47:29 by mchett           ###   ########.fr       */
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
	mlx->mouse->x = 0;
	mlx->mouse->y = 0;
	mlx->mouse->right = 0;
	return (mlx);
}
