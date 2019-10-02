/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:34:14 by mchett            #+#    #+#             */
/*   Updated: 2019/10/02 15:03:41 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static char	*join(char *str, char *tab)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	j = 0;
	if (str)
		i = ft_strlen(str);
	if (tab)
		j = ft_strlen(tab);
	ptr = (char *)malloc(sizeof(*ptr) * (i + j + 1));
	ft_memcpy(ptr, str, i);
	ft_memcpy(ptr + i, tab, j);
	ptr[i + j] = '\0';
	free(str);
	ft_bzero(tab, BUFF_SIZE + 1);
	return (ptr);
}

int			something(char **str, char **tmp, char **line)
{
	int		count;
	char	*ptr;

	count = 0;
	if ((!str) && (!(*tmp)))
		return (0);
	*str = join(*str, *tmp);
	while ((*str)[count] != ENDL && (*str)[count])
		count++;
	if ((*str)[count] == ENDL)
		(*str)[count] = END;
	else
		count = -1;
	if (count > -1)
	{
		*line = ft_strdup(*str);
		ptr = *str;
		*str = ft_strdup(*str + count + 1);
		free(ptr);
		return (1);
	}
	return (0);
}

int			biwsl(int fd, char **tmp, char *(*str)[1000], char **line)
{
	int result;

	result = 0;
	while (read(fd, *tmp, BUFF_SIZE) > 0)
	{
		result = something(&((*str)[fd]), &(*tmp), line);
		ft_strdel(&(*tmp));
		if (result == 1)
			return (1);
		*tmp = ft_strnew(BUFF_SIZE);
	}
	return (result);
}

int			get_next_line(int const fd, char **line)
{
	static char	*str[1000];
	char		*tmp;
	int			result;

	result = 0;
	tmp = ft_strnew(BUFF_SIZE);
	if (!tmp || read(fd, tmp, 0) < 0 || fd < 0
			|| fd > 999 || !line || BUFF_SIZE < 0)
	{
		ft_strdel(&tmp);
		return (-1);
	}
	if (biwsl(fd, &tmp, &str, line) == 1)
		return (1);
	if (something(&str[fd], &tmp, line) == 1)
		result = 1;
	ft_strdel(&tmp);
	if (ft_strlen(str[fd]) > 0 && result != 1)
	{
		*line = ft_strdup(str[fd]);
		ft_strdel(&str[fd]);
		result = 1;
	}
	return (result);
}
