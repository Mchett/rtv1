/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:12:53 by mchett            #+#    #+#             */
/*   Updated: 2019/10/03 12:54:57 by mchett           ###   ########.fr       */
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
