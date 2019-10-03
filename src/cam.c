/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 16:04:43 by mchett            #+#    #+#             */
/*   Updated: 2019/10/03 15:19:03 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	cam_data(t_mlx *mlx, char **str)
{
	int i;

	i = -1;
	mlx->cam.pos.x = (double)(ft_atoi(str[1]));
	mlx->cam.pos.y = (double)(ft_atoi(str[2]));
	mlx->cam.pos.z = (double)(ft_atoi(str[3]));
	mlx->cam.rot.x = (double)(ft_atoi(str[4]));
	mlx->cam.rot.y = (double)(ft_atoi(str[5]));
	mlx->cam.rot.z = (double)(ft_atoi(str[6]));
	mlx->cam_is++;
	while (++i <= 6)
		free(str[i]);
	free(str);
}
