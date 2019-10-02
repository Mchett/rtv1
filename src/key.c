/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 11:23:09 by mchett            #+#    #+#             */
/*   Updated: 2019/10/01 11:53:32 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"



int		key_hook(int keycode, t_mlx *m)
{
	if (keycode == 53)
		exit(EXIT_SUCCESS);
	if (keycode == 257)
	{
		(void)m;
	}
	/*if (keycode == 126)
		m->f->my -= 0.1 / m->f->z;
	else if (keycode == 123)
		m->f->mx -= 0.1 / m->f->z;
	if (keycode == 125)
		m->f->my += 0.1 / m->f->z;
	else if (keycode == 124)
		m->f->mx += 0.1 / m->f->z;
	else if (keycode == 37)
		m->logcolor += 1;
	else if (keycode == 24 || keycode == 27)
		iter(keycode, m);*/
	//ft_putimage(m);
	return (0);
}
