/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 15:28:53 by mchett            #+#    #+#             */
/*   Updated: 2019/10/03 15:29:58 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		line_valid(char *line)
{
	if (ft_strncmp("cam: ", line, 5) == 0)
		return (1);
	if (ft_strncmp("light: ", line, 7) == 0)
		return (1);
	if (ft_strncmp("sphere: ", line, 8) == 0)
		return (1);
	if (ft_strncmp("cone: ", line, 6) == 0)
		return (1);
	if (ft_strncmp("cylinder: ", line, 10) == 0)
		return (1);
	if (ft_strncmp("plane: ", line, 7) == 0)
		return (1);
	if (ft_strncmp("ambient: ", line, 9) == 0)
		return (1);
	ft_error("Wrong input");
	return (0);
}

int		val_2(char *str)
{
	int	i;

	if (str[0] == '-' || str[0] == '+')
		i = 1;
	else
		i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			i++;
		else
			ft_error("Input is not number");
	}
	return (1);
}

void	val_1(char **str, int k)
{
	int i;

	i = 0;
	while (++i <= k)
		if (!str[i] || (ft_atoi(str[i]) == 0 && str[i][0] != '0') ||
				str[k + 1] != NULL || !val_2(str[i]))
			ft_error("Wrong input file");
	i = -1;
}
