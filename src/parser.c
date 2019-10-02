/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 14:53:31 by mchett            #+#    #+#             */
/*   Updated: 2019/10/02 16:03:02 by mchett           ###   ########.fr       */
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
		if (!str[i] || (atoi(str[i]) == 0 && str[i][0] != '0') ||
				str[k + 1] != NULL || !val_2(str[i]))
			ft_error("Wrong input file");
	i = -1;
	while (++i <= k)
		free(str[i]);
	free(str);
}

void	validation(char **str)
{
	int i;

	i = 0;
	if (ft_strequ(str[0], "cam:"))
		val_1(str, 6);
	else if (ft_strequ(str[0], "sphere:"))
		val_1(str, 8);
	else if (ft_strequ(str[0], "plane:"))
		val_1(str, 10);
	else if (ft_strequ(str[0], "cylinder:") || ft_strequ(str[0], "cone:"))
		val_1(str, 11);
	else if (ft_strequ(str[0], "light:"))
		val_1(str, 4);
	else if (ft_strequ(str[0], "ambient:"))
		val_1(str, 1);
}

void	obj_counter(t_mlx *mlx, char *str)
{
	if (ft_strequ(str, "sphere:") || ft_strequ(str, "plane:") ||
		ft_strequ(str, "cylinder:") || ft_strequ(str, "cone:"))
		mlx->obj_num++;
	else if (ft_strequ(str, "light:"))
		mlx->light_num++;
	else if (ft_strequ(str, "cam:"))
		mlx->cam_is++;
}

void	split_parse(char **str, t_mlx *mlx)
{
	if (ft_strequ(str[0], "cam:"))
		cam_data(mlx, str);
	else if (ft_strequ(str[0], "sphere:"))
		sphere_data(mlx, str);
	else if (ft_strequ(str[0], "plane:"))
		plane_data(mlx, str);
	else if (ft_strequ(str[0], "cylinder:"))
		cylinder_data(mlx, str);
	else if (ft_strequ(str[0], "cone:"))
		cone_data(mlx, str);
	else if (ft_strequ(str[0], "light:"))
		light_data(mlx, str);
	else if (ft_strequ(str[0], "ambient:"))
		ambient_data(mlx, str);
}

void	ft_parse(t_mlx *mlx, char *str)
{
	char	*line;
	int		fd;
	char	**spl_res;

	fd = 0;
	line = NULL;
	if ((fd = open(str, O_RDONLY)) < 0)
		ft_error("Can't open the file");
	while (get_next_line(fd, &line) > 0)
	{
		line_valid(line);
		spl_res = ft_strsplit(line, ' ');
		obj_counter(mlx, spl_res[0]);
		validation(spl_res);
		split_parse(spl_res, mlx);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	if (mlx->cam_is != 1 || mlx->light_num == 0 || mlx->obj_num < 1)
		ft_error("Have no objects/lights/camera");
	close(fd);
}
