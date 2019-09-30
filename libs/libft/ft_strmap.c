/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 17:46:56 by mchett            #+#    #+#             */
/*   Updated: 2018/12/06 17:13:00 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
		new_str[i] = f(s[i]);
	return (new_str);
}
