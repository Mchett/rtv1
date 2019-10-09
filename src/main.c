/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 12:30:30 by mchett            #+#    #+#             */
/*   Updated: 2019/10/04 16:46:02 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"
#include <stdio.h>

int		color(t_rgb rgb, double p)
{
	return (((int)(rgb.r * p) << 16 | (int)(rgb.g * p) << 8 |
	(int)(rgb.b * p)));
}

int		ft_close(void)
{
	exit(0);
}

void	draw(t_mlx *mlx, t_object **ob_buf, t_light **lt_buf)
{
	if (mlx->mlx_ptr != NULL)
	{
		mlx->ob_buf = ob_buf;
		mlx->lt_buf = lt_buf;
		mlx_hook(mlx->win_ptr, 2, 4, key_hook, mlx);
		ft_putimage(mlx);
		mlx_hook(mlx->win_ptr, 17, 0, ft_close, mlx);
	}
}

void	ft_error(char *str)
{
	ft_putendl(str);
	exit(1);
}

int		main(int argc, char **argv)
{
	t_mlx		*mlx;
	void		*init;
	t_object	**ob_buf;
	t_light		**lt_buf;

	ob_buf = NULL;
	lt_buf = NULL;
	if (argc != 2)
		ft_error("Usage input file");
	init = mlx_init();
	mlx = ft_init(argv[1], init);
	ft_parse(mlx, argv[1]);
	init_buf(&ob_buf, &lt_buf, mlx);
	mlx->ray.orig.x = mlx->cam.pos.x;
	mlx->ray.orig.y = mlx->cam.pos.y;
	mlx->ray.orig.z = mlx->cam.pos.z;
	draw(mlx, ob_buf, lt_buf);
	mlx_loop(init);
	free(mlx);
	return (0);
}
