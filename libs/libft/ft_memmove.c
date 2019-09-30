/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:32:47 by mchett            #+#    #+#             */
/*   Updated: 2018/12/06 16:31:36 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destptr, const void *srcptr, size_t num)
{
	unsigned char *d;
	unsigned char *s;

	d = (unsigned char *)destptr;
	s = (unsigned char *)srcptr;
	if (destptr == NULL && srcptr == NULL)
		return (NULL);
	if (d < s)
		while (num--)
			*d++ = *s++;
	else
	{
		d += num;
		s += num;
		while (num--)
			*--d = *--s;
	}
	return (destptr);
}
