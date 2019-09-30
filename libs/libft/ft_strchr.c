/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:20:24 by mchett            #+#    #+#             */
/*   Updated: 2018/11/26 15:22:54 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *string, int symbol)
{
	char *res;

	res = NULL;
	while (*string != '\0')
	{
		if (*string == symbol)
			return ((char*)string);
		string++;
	}
	if (symbol == '\0')
		res = (char*)string;
	return (res);
}
