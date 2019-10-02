/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:43:48 by mchett            #+#    #+#             */
/*   Updated: 2019/10/02 16:12:06 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libs/libft/libft.h" 
# include "../libs/minilibx/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# define DTR(a)	((double)a * (M_PI / 180))
# define W_W 800
# define W_H 800
# define V_W 40
# define V_H 40
# define SPHERE 1
# define PLANE 2
# define CYLINDER 3
# define CONE 4
# define EPS 0.000001
# define OBJ mlx->obj[mlx->clos_obj]
# define SPL spl_res[0]
# define OBJP mlx->obj[mlx->obj_counter]
# define BUFF_SIZE 1000
# define ENDL '\n'
# define END '\0'

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

typedef	struct				s_cam
{
	t_vect					pos;
	t_vect					rot;
}							t_cam;

typedef	struct				s_light
{
	t_vect					pos;
	t_vect					p;
	t_vect					n;
	double					inten;
	double					new_inten;
}							t_light;

typedef struct				s_sphere
{
	t_vect					*centr;
	double					r;
}							t_sphere;

typedef struct				s_rgb
{
	int						r;
	int						g;
	int						b;
}							t_rgb;

typedef	struct				s_ray
{
	t_vect					orig;
	t_vect					dir;
}							t_ray;

typedef struct				s_object
{
	t_vect					pos;
	int						col1;
	t_rgb					col2;
	t_vect					rot;
	double					r;
	double					t;
	int						name;
	double					specular;
}							t_object;

typedef struct				s_mlx
{
	void					*mlx_ptr;
	void					*win_ptr;
	t_image					*image;
	t_mouse					*mouse;
	t_cam					cam;
	t_object				*obj;
	int						obj_num;
	int						light_num;
	int						clos_obj;
	int						obj_counter;
	int						light_counter;
	int						cam_is;
	double					min_t;
	double					ambient;
	t_light					*light;

}							t_mlx;

t_sphere	*new_sphere(double r, t_vect *p);

double		vect_proizv_v(t_vect *v, t_vect *b);

int			ray_intersect(t_vect *orig, t_vect *dir,t_sphere *s);

t_mlx		*mlxdel(t_mlx *mlx);

void		ft_putimage(t_mlx *mlx, t_sphere *s);

void		render(t_sphere *sphere, t_image *img);

void		image_set_pixel(t_image *image, int x, int y, int color);

t_image		*new_image(t_mlx *mlx);

t_mlx		*ft_init(char *str, void *ini);

int			key_hook(int keycode, t_mlx *m);

void		ft_error(char *str);

void		ft_parse(t_mlx *mlx, char *str);

int			get_next_line(const int fd, char **line);

void	ambient_data(t_mlx *mlx, char **str);

void	cam_data(t_mlx *mlx, char **str);

void	cone_data(t_mlx *mlx, char **str);

void	cylinder_data(t_mlx *mlx, char **str);

void	light_data(t_mlx *mlx, char **str);

void	plane_data(t_mlx *mlx, char **str);

void	sphere_data(t_mlx *mlx, char **str);



//vectors operations
t_vect		*new_vect2(double x, double y, double z);
t_vect		*new_vect(t_vect *s, t_vect *e);
t_vect		*vect_sum(t_vect *v1, t_vect *v2);
double		vect_proizv(t_vect *v1, t_vect *v2);
double		vect_len(t_vect *v1);
t_vect		*vect_scale(t_vect *v1, double t);
t_vect		*vect_norm(t_vect *v1);
t_vect		*vect_sub(t_vect *v1, t_vect *v2);
t_vect		*vect_rot(t_vect *d, t_vect *r);
t_vect		*vect_rotx(t_vect *d, double a);
t_vect		*vect_roty(t_vect *d, double a);
t_vect		*vect_rotz(t_vect *d, double a);
#endif
