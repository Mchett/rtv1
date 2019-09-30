/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 12:55:06 by mchett            #+#    #+#             */
/*   Updated: 2018/12/12 12:02:47 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	int		i;
	int		count;
	char	*dest;

	dest = NULL;
	count = 0;
	i = 0;
	while (src[i] != '\0')
	{
		i++;
		count++;
	}
	dest = (char*)malloc(count + 1);
	if (dest != NULL)
	{
		i = 0;
		while (i <= count)
		{
			dest[i] = src[i];
			i++;
		}
	}
	return (dest);
}
