/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:12:53 by mchett            #+#    #+#             */
/*   Updated: 2018/12/06 14:48:11 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[j] == s2[i] && i < ft_strlen(s2))
	{
		j++;
		i++;
	}
	if (j == ft_strlen(s1) + 1)
		return (0);
	return ((unsigned char)s1[j] - (unsigned char)s2[i]);
}
