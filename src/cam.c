/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 16:04:43 by mchett            #+#    #+#             */
/*   Updated: 2019/10/02 16:22:19 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	cam_data(t_mlx *mlx, char **str)
{
	int i;

	i = -1;
	mlx->cam.pos.x = (double)(atoi(str[1]));
	mlx->cam.pos.y = (double)(atoi(str[2]));
	mlx->cam.pos.z = (double)(atoi(str[3]));
	mlx->cam.rot.x = (double)(atoi(str[4]));
	mlx->cam.rot.y = (double)(atoi(str[5]));
	mlx->cam.rot.z = (double)(atoi(str[6]));
	while (++i <= 6)
		free(str[i]);
	free(str);
}