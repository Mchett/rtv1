/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:17:45 by mchett            #+#    #+#             */
/*   Updated: 2018/11/26 15:23:03 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int symbol)
{
	char *res;

	res = NULL;
	while (*string != '\0')
	{
		if (*string == symbol)
			res = (char*)string;
		string++;
	}
	if (symbol == '\0')
		res = (char*)string;
	return (res);
}
