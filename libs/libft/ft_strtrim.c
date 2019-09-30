/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 14:06:48 by mchett            #+#    #+#             */
/*   Updated: 2018/12/06 15:43:23 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	has_whitespaces(char const *str, size_t j)
{
	size_t i;
	size_t res;

	i = 0;
	while (ft_is_space(str[i]) == 1)
		i++;
	res = j - i;
	if (i == j)
		return (0);
	i = j - 1;
	while (ft_is_space(str[i]) == 1)
		i--;
	res = res - (j - i);
	return (res);
}

char			*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*new_str;
	size_t	new_size;

	if (s == NULL)
		return (NULL);
	i = 0;
	k = 0;
	j = ft_strlen(s);
	new_size = has_whitespaces(s, j) + 1;
	new_str = ft_strnew(new_size);
	if (new_str == NULL)
		return (NULL);
	while (ft_is_space(s[i]) == 1)
		i++;
	while (k < new_size)
	{
		new_str[k++] = s[i++];
	}
	return (new_str);
}
