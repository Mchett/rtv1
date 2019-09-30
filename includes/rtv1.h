/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:43:48 by mchett            #+#    #+#             */
/*   Updated: 2019/09/30 17:28:58 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define W_W	1920
# define W_H	1080
# include "../libs/libft/libft.h" 
# include "../libs/minilibx/mlx.h"
# include <math.h>

typedef struct				s_image
{
	void					*ptr;
	char					*data;
	int						bitspp;
	int						string;
	int						endian;
}							t_image;

typedef struct				s_mouse
{
	int						x;
	int						y;
	int						prevx;
	int						prevy;
	int						down;
	int						right;
}							t_mouse;

typedef struct				s_vect
{
	double					x;
	double					y;
	double					z;
}							t_vect;

typedef struct				s_sphere
{
	t_vect					*centr;
	double					r;
}							t_sphere;

typedef struct				s_cone
{
}							t_cone;

typedef struct				s_plane
{
}							t_plane;

typedef struct				s_cylinder
{
}							t_cylinder;

typedef struct				s_mlx
{


	void					*mlx_ptr;
	void					*win_ptr;
	t_image					*image;
	t_mouse					*mouse;
}							t_mlx;

t_vect		*new_vect2(double x, double y, double z);

t_sphere	*new_sphere(double r, t_vect *p);

double		vect_proizv_v(t_vect *v, t_vect *b);

t_vect		*new_vect(t_vect *s, t_vect *e);

int			ray_intersect(t_vect *orig, t_vect *dir,t_sphere *s);

t_vect		*vect_norm(t_vect *v);

t_mlx		*mlxdel(t_mlx *mlx);

void		ft_putimage(t_mlx *mlx, t_sphere *s);

void		render(t_sphere *sphere, t_image *img);

void		image_set_pixel(t_image *image, int x, int y, int color);

t_image		*new_image(t_mlx *mlx);

t_mlx		*ft_init(char *str, void *ini);

#endif
