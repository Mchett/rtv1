/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:03:41 by mchett            #+#    #+#             */
/*   Updated: 2019/10/02 16:21:22 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	cylinder_data(t_mlx *mlx, char **str)
{
	int i;

	i = -1;
	OBJP.pos.x = (double)(atoi(str[1]));
	OBJP.pos.y = (double)(atoi(str[2]));
	OBJP.pos.z = (double)(atoi(str[3]));
	OBJP.r = (double)(atoi(str[4])) / 10;
	OBJP.rot.x = (double)(atoi(str[5]));
	OBJP.rot.y = (double)(atoi(str[6]));
	OBJP.rot.z = (double)(atoi(str[7]));
	if (OBJP.r < 0.1 || atoi(str[8]) < 0 || atoi(str[9]) < 0
		|| atoi(str[10]) < 0)
		ft_error("Wrong input for cylinder");
	OBJP.col2.r = atoi(str[8]);
	OBJP.col2.g = atoi(str[9]);
	OBJP.col2.b = atoi(str[10]);
	OBJP.specular = (double)(atoi(str[11]));
	OBJP.name = CYLINDER;
	//mlx->obj_counter++;
	while (++i <= 11)
		free(str[i]);
	free(str);
}
