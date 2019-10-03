/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 12:30:30 by mchett            #+#    #+#             */
/*   Updated: 2019/10/03 15:22:31 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		ft_close(void)
{
	exit(0);
}

void	draw(t_mlx *mlx)
{
	if (mlx->mlx_ptr != NULL)
	{
		ft_putimage(mlx);
		mlx_hook(mlx->win_ptr, 2, 4, key_hook, mlx);
		//mlx_hook(mlx->win_ptr, 5, 0, mouse_scroll, mlx);
		//mlx_hook(mlx->win_ptr, 4, 0, mouse_scroll_down, mlx);
		//mlx_hook(mlx->win_ptr, 6, 0, ft_mouse_move, mlx);
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
	t_mlx	*mlx;
	void	*init;

	if (argc != 2)
		ft_error("Usage input file");
	init = mlx_init();
	mlx = ft_init(argv[1], init);
	ft_parse(mlx, argv[1]);
	mlx->ray.orig.x = mlx->cam.pos.x;
	mlx->ray.orig.y = mlx->cam.pos.y;
	mlx->ray.orig.z = mlx->cam.pos.z;
	draw(mlx);
	mlx_loop(init);
	free(mlx);
	return (0);
}
