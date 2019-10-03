/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 11:23:09 by mchett            #+#    #+#             */
/*   Updated: 2019/10/03 15:12:43 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		key_hook(int keycode, t_mlx *m)
{
	
	if (keycode == 53)
		exit(EXIT_SUCCESS);
	if (keycode == 126)
		m->ray.orig.z +=10;
	else if(keycode == 124)
		m->ray.orig.x +=10;
	else if(keycode == 125)
		m->ray.orig.z -=10;
	else if(keycode == 123)
	{
		printf("%d\n", keycode);
		m->ray.orig.x -= 10;
	}
	ft_putimage(m);
	return (0);
}
