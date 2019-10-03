/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 14:53:31 by mchett            #+#    #+#             */
/*   Updated: 2019/10/03 12:54:46 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		line_valid(char *line)
{
	if (ft_strncmp("cam: ", line, 5) == 0)
	{
		//printf("cam\n");
		return (1);
	}
	if (ft_strncmp("light: ", line, 7) == 0)
	{
		//printf("light\n");
		return (1);
	}
	if (ft_strncmp("sphere: ", line, 8) == 0)
	{
		//printf("sphere\n");
		return (1);
	}
	if (ft_strncmp("cone: ", line, 6) == 0)
	{
		//printf("cone\n");
		return (1);
	}
	if (ft_strncmp("cylinder: ", line, 10) == 0)
	{
		//printf("cylinder\n");
		return (1);
	}
	if (ft_strncmp("plane: ", line, 7) == 0)
	{
		//printf("plane\n");
		return (1);
	}
	if (ft_strncmp("ambient: ", line, 9) == 0)
	{
		//printf("ambient\n");
		return (1);
	}
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

void	validation(char **str)
{
	int i;

	i = 0;
	if (ft_strcmp(str[0], "cam:") == 0)
		val_1(str, 6);
	else if (ft_strcmp(str[0], "sphere:")  == 0)
		val_1(str, 8);
	else if (ft_strcmp(str[0], "plane:")  == 0)
		val_1(str, 10);
	else if (ft_strcmp(str[0], "cylinder:")  == 0 || ft_strcmp(str[0], "cone:") == 0)
		val_1(str, 11);
	else if (ft_strcmp(str[0], "light:") == 0)
		val_1(str, 4);
	else if (ft_strcmp(str[0], "ambient:") == 0)
		val_1(str, 1);
}

void	obj_counter(t_mlx *mlx, char *str, int fd, char *line)
{
	char	**res;

	if ((fd = open(str, O_RDONLY)) < 0)
		ft_error("Can't open the file");
	while (get_next_line(fd, &line) > 0)
	{
		res = ft_strsplit(line, ' ');
		if (ft_strcmp(res[0], "sphere:")  == 0 || ft_strcmp(res[0], "plane:")  == 0 ||
			ft_strcmp(res[0], "cylinder:")  == 0 || ft_strcmp(res[0], "cone:") == 0)
				mlx->obj_num++;
		else if (ft_strcmp(res[0], "light:") == 0)
			mlx->light_num++;
		 else if (ft_strcmp(res[0], "cam:") == 0)
			mlx->cam_is++;
		ft_strdel(&line);
	}
	ft_strdel(&line);
	if (mlx->cam_is != 1 || mlx->light_num == 0 || mlx->obj_num < 1)
		ft_error("Have no objects/lights/camera");
	mlx->obj = ft_memalloc(sizeof(t_object) * mlx->obj_num);
	mlx->light = ft_memalloc(sizeof(t_light) * mlx->light_num);
	close(fd);
}

void	split_parse(char **str, t_mlx *mlx)
{
	if (ft_strcmp(str[0], "cam:") == 0)
		cam_data(mlx, str);
	else if (ft_strcmp(str[0], "sphere:") == 0)
		sphere_data(mlx, str);
	else if (ft_strcmp(str[0], "plane:") == 0)
		plane_data(mlx, str);
	else if (ft_strcmp(str[0], "cylinder:") == 0)
		cylinder_data(mlx, str);
	else if (ft_strcmp(str[0], "cone:") == 0)
		cone_data(mlx, str);
	else if (ft_strcmp(str[0], "light:") == 0)
		light_data(mlx, str);
	else if (ft_strcmp(str[0], "ambient:") == 0)
		ambient_data(mlx, str);
}

void	ft_parse(t_mlx *mlx, char *str)
{
	char	*line;
	int		fd;
	char	**spl_res;

	line = NULL;
	obj_counter(mlx, str, 0, line);
	if ((fd = open(str, O_RDONLY)) < 0)
		ft_error("Can't open the file");

	while (get_next_line(fd, &line) > 0)
	{
		line_valid(line);
		spl_res = ft_strsplit(line, ' ');
		validation(spl_res);
		split_parse(spl_res, mlx);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	
	close(fd);
}
