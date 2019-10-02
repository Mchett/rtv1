/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 16:04:58 by mchett            #+#    #+#             */
/*   Updated: 2019/10/02 16:16:00 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	light_data(t_mlx *mlx, char **str)
{
	int i;

	i = -1;
	mlx->light[mlx->light_counter].pos.x = (double)(atoi(str[1]));
	mlx->light[mlx->light_counter].pos.y = (double)(atoi(str[2]));
	mlx->light[mlx->light_counter].pos.z = (double)(atoi(str[3]));
	mlx->light[mlx->light_counter].inten = (double)(atoi(str[4])) / 100;
	if (mlx->light[mlx->light_counter].inten < 0)
		ft_error("Wrong intensity parameter");
	//mlx->light_counter++;
	while (++i <= 4)
		free(str[i]);
	free(str);
}
