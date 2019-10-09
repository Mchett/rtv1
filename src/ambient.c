/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanfred <cmanfred@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 16:05:12 by mchett            #+#    #+#             */
/*   Updated: 2019/10/05 14:32:33 by cmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	ambient_data(t_mlx *mlx, char **str)
{
	int i;

	i = -1;
	if (ft_check_len(str) != 2)
		ft_error("Wrong input");
	mlx->ambient = (double)(ft_atoi(str[1])) / 100;
	if (mlx->ambient < 0)
		ft_error("Wrong intensity parameter");
}
