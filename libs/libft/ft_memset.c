/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 14:16:42 by mchett            #+#    #+#             */
/*   Updated: 2018/11/26 15:02:41 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *memptr, int val, size_t num)
{
	size_t	i;
	char	*res;

	i = -1;
	res = memptr;
	while (++i < num)
		*(res + i) = val;
	return (memptr);
}
