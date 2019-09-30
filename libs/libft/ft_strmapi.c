/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 17:50:24 by mchett            #+#    #+#             */
/*   Updated: 2018/12/06 17:14:36 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_str;
	int		i;

	if (s == NULL)
		return (NULL);
	new_str = ft_strnew(ft_strlen(s));
	if (new_str == NULL)
		return (NULL);
	i = -1;
	while (s[++i])
		new_str[i] = f(i, s[i]);
	return (new_str);
}
