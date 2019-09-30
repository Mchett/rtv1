/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:26:25 by mchett            #+#    #+#             */
/*   Updated: 2018/12/06 16:30:48 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destptr, const void *srcptr, size_t num)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)destptr;
	s = (unsigned char *)srcptr;
	if (destptr == NULL && srcptr == NULL)
		return (NULL);
	while (num--)
		*d++ = *s++;
	return (destptr);
}
