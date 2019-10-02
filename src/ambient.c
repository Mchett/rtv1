/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 16:05:12 by mchett            #+#    #+#             */
/*   Updated: 2019/10/02 16:23:53 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	ambient_data(t_mlx *mlx, char **str)
{
	int i;

		i = -1;
		mlx->ambient = (double)(atoi(str[1])) / 100;
		if (mlx->ambient < 0)
			ft_error("Wrong intensity parameter");
		while (++i <= 1)
			free(str[i]);
		free(str);
}