

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <pthread.h>

# include "libs/libft/libft.h"


# define DWIDTH 800
# define DHEIGHT 800
# define V_W 40
# define V_H 40
# define SPHERE 1
# define PLANE 2
# define CYLINDER 3
# define CONE 4
# define EPS 0.000001
# define OBJ sdl->obj[sdl->clos_obj]
# define SPL spl_res[0]
# define OBJP sdl->obj[sdl->obj_counter]

typedef struct	s_vec
{
	double		x;
	double		y;
	double		z;
}				t_vec;

typedef	struct		s_light
{
	t_vec			pos;
	t_vec			p;
	t_vec			n;
	double			inten;
	double			new_inten;
}					t_light;

typedef struct		s_rgb
{
	unsigned char	rgb[3];
}					t_rgb;

typedef struct		s_object
{
	t_vec			pos;
	t_rgb			col;
	t_vec			rot;
	double			r;
	double			t;
	int				name;
	double			specular;
}					t_object;

typedef	struct		s_cam
{
	t_vec			pos;
	t_vec			rot;
}					t_cam;

typedef	struct		s_ray
{
	t_vec			orig;
	t_vec			dir;
}					t_ray;

typedef struct		s_sdl
{
	SDL_Window		*wind;
	SDL_Renderer	*rend;
	t_cam			cam;
	t_object		*obj;
	int				obj_num;
	int				light_num;
	int				clos_obj;
	int				obj_counter;
	int				light_counter;
	int				cam_is;
	double			min_t;
	double			ambient;
	t_light			*light;
}					t_sdl;


t_vec			vec_sum(t_vec v1, t_vec v2);
double			vec_dot(t_vec v1, t_vec v2);
double			vec_len(t_vec v1);
t_vec			vec_scale(t_vec v1, double t);
t_vec			vec_norm(t_vec v1);
t_vec			vec_sub(t_vec v1, t_vec v2);
t_vec			vec_rot(t_vec d, t_vec r);
t_vec			vec_rotx(t_vec d, double a);
t_vec			vec_roty(t_vec d, double a);
t_vec			vec_rotz(t_vec d, double a);
void				validation_init(char *arg, t_sdl *sdl, int fd, int i);
void				ft_parse(char *arg, t_sdl *sdl);
void				ft_error(char *str);
void				ray_trace_init(t_sdl *sdl, t_ray *ray);
void				get_intensity(t_sdl *sdl, t_light *light,
		t_vec v, double s);
void				sphere(t_sdl *sdl, t_ray *ray, int i, t_object *obj);
void				sphere_data(t_sdl *sdl, char **str);
double				sphere_intersect(t_vec o, t_vec dir, t_object *obj);
t_vec				sphere_normal(t_ray *ray, t_object *obj);
void				plane(t_sdl *sdl, t_ray *ray, int i, t_object *obj);
void				plane_data(t_sdl *sdl, char **str);
double				plane_intersect(t_vec o, t_vec dir, t_object *obj);
t_vec				plane_normal(t_ray *ray, t_object *obj);
void				cylinder(t_sdl *sdl, t_ray *ray, int i, t_object *obj);
void				cylinder_data(t_sdl *sdl, char **str);
double				cylinder_intersect(t_vec o, t_vec dir, t_object *obj);
t_vec				cyl_normal_calc(t_ray *ray, t_object *obj);
double				get_t(double a, double b, double d);
void				cone(t_sdl *sdl, t_ray *ray, int i, t_object *obj);
void				cone_data(t_sdl *sdl, char **str);
double				cone_intersect(t_vec o, t_vec dir, t_object *obj);
t_vec				cone_normal_calc(t_ray *ray, t_object *obj);
void				light(t_sdl *sdl, t_ray *ray);
void				cam_data(t_sdl *sdl, char **str);
void				light_data(t_sdl *sdl, char **str);
int					val_2(char *str);

double	vec_dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	vec_len(t_vec v1)
{
	return (sqrt(vec_dot(v1, v1)));
}

t_vec	vec_norm(t_vec v1)
{
	double inv;

	inv = 1 / vec_len(v1);
	return (vec_scale(v1, inv));
}
t_vec	vec_rot(t_vec d, t_vec r)
{
	d = vec_rotx(d, DTR(r.x));
	d = vec_roty(d, DTR(r.y));
	d = vec_rotz(d, DTR(r.z));
	return (d);
}

t_vec	vec_rotx(t_vec d, double a)
{
	t_vec r;

	r.x = d.x;
	r.y = d.y * cos(a) - d.z * sin(a);
	r.z = d.y * sin(a) + d.z * cos(a);
	return (r);
}

t_vec	vec_roty(t_vec d, double a)
{
	t_vec r;

	r.x = d.x * cos(a) + d.z * sin(a);
	r.y = d.y;
	r.z = d.z * cos(a) - d.x * sin(a);
	return (r);
}

t_vec	vec_rotz(t_vec d, double a)
{
	t_vec	r;

	r.x = d.x * cos(a) - d.y * sin(a);
	r.y = d.x * sin(a) + d.y * cos(a);
	r.z = d.z;
	return (r);
}

t_vec	vec_scale(t_vec v1, double t)
{
	v1.x *= t;
	v1.y *= t;
	v1.z *= t;
	return (v1);
}

t_vec	vec_sub(t_vec v1, t_vec v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}

t_vec	vec_sum(t_vec v1, t_vec v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}


void	cone_data(t_sdl *sdl, char **str)
{
	int i;

	i = -1;
	OBJP.pos.x = (double)(atoi(str[1]));
	OBJP.pos.y = (double)(atoi(str[2]));
	OBJP.pos.z = (double)(atoi(str[3]));
	OBJP.r = (double)(atoi(str[4])) / 10;
	OBJP.rot.x = (double)(atoi(str[5])) / 10;
	OBJP.rot.y = (double)(atoi(str[6])) / 10;
	OBJP.rot.z = (double)(atoi(str[7])) / 10;
	if (OBJP.r < 0.1 || atoi(str[8]) < 0 || atoi(str[9]) < 0
		|| atoi(str[10]) < 0)
		ft_error("Wrong input for cone");
	OBJP.col.rgb[0] = (unsigned char)(atoi(str[8]));
	OBJP.col.rgb[1] = (unsigned char)(atoi(str[9]));
	OBJP.col.rgb[2] = (unsigned char)(atoi(str[10]));
	OBJP.specular = (double)(atoi(str[11]));
	OBJP.name = CONE;
	sdl->obj_counter++;
	while (++i <= 11)
		free(str[i]);
	free(str);
}

double	cone_intersect(t_vec o, t_vec dir, t_object *obj)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vec	x;

	x = vec_sub(o, obj->pos);
	a = vec_dot(dir, obj->rot);
	a = vec_dot(dir, dir) - (1 + obj->r * obj->r) * a * a;
	b = 2 * (vec_dot(dir, x) - (1 + obj->r * obj->r) *
		vec_dot(dir, obj->rot) * vec_dot(x, obj->rot));
	c = vec_dot(x, x) - (1 + obj->r * obj->r) * pow(vec_dot(x, obj->rot), 2);
	d = b * b - 4 * a * c;
	if (d < EPS)
		return (-1);
	return (get_t(a, b, d));
}

t_vec	cone_normal_calc(t_ray *ray, t_object *obj)
{
	double	m;
	t_vec	n;
	t_vec	p;

	m = obj->t * vec_dot(ray->dir, obj->rot) +
	vec_dot(vec_sub(ray->orig, obj->pos), obj->rot);
	p = vec_sum(ray->orig, vec_scale(ray->dir, obj->t));
	n = vec_scale(vec_scale(obj->rot, m), (1 + obj->r * obj->r));
	n = vec_norm(vec_sub(vec_sub(p, obj->pos), n));
	if (vec_dot(ray->dir, n) > EPS)
		n = vec_scale(n, -1);
	return (n);
}

void	cone(t_sdl *sdl, t_ray *ray, int i, t_object *obj)
{
	obj->t = cone_intersect(ray->orig, ray->dir, obj);
	obj->rot = vec_norm(obj->rot);
	if (obj->t > 0 && obj->t < sdl->min_t)
	{
		sdl->min_t = obj->t;
		sdl->clos_obj = i;
	}
}

void	cylinder_data(t_sdl *sdl, char **str)
{
	int i;

	i = -1;
	OBJP.pos.x = (double)(atoi(str[1]));
	OBJP.pos.y = (double)(atoi(str[2]));
	OBJP.pos.z = (double)(atoi(str[3]));
	OBJP.r = (double)(atoi(str[4])) / 10;
	OBJP.rot.x = (double)(atoi(str[5]));
	OBJP.rot.y = (double)(atoi(str[6]));
	OBJP.rot.z = (double)(atoi(str[7]));
	if (OBJP.r < 0.1 || atoi(str[8]) < 0 || atoi(str[9]) < 0
		|| atoi(str[10]) < 0)
		ft_error("Wrong input for cylinder");
	OBJP.col.rgb[0] = (unsigned char)(atoi(str[8]));
	OBJP.col.rgb[1] = (unsigned char)(atoi(str[9]));
	OBJP.col.rgb[2] = (unsigned char)(atoi(str[10]));
	OBJP.specular = (double)(atoi(str[11]));
	OBJP.name = CYLINDER;
	sdl->obj_counter++;
	while (++i <= 11)
		free(str[i]);
	free(str);
}

double	cylinder_intersect(t_vec o, t_vec dir, t_object *obj)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vec	x;

	x = vec_sub(o, obj->pos);
	a = vec_dot(dir, dir) - pow(vec_dot(dir, obj->rot), 2);
	b = 2 * (vec_dot(dir, x) - (vec_dot(dir, obj->rot) * vec_dot(x, obj->rot)));
	c = vec_dot(x, x) - pow(vec_dot(x, obj->rot), 2) - pow(obj->r, 2);
	d = b * b - 4 * a * c;
	if (d < 0)
		return (-1);
	return (get_t(a, b, d));
}

t_vec	cyl_normal_calc(t_ray *ray, t_object *obj)
{
	double	m;
	t_vec	n;
	t_vec	p;

	m = obj->t * vec_dot(ray->dir, obj->rot) +
	vec_dot(vec_sub(ray->orig, obj->pos), obj->rot);
	p = vec_sum(ray->orig, vec_scale(ray->dir, obj->t));
	n = vec_norm(vec_sub(vec_sub(p, obj->pos), vec_scale(obj->rot, m)));
	if (vec_dot(ray->dir, n) > EPS)
		n = vec_scale(n, -1);
	return (n);
}

void	cylinder(t_sdl *sdl, t_ray *ray, int i, t_object *obj)
{
	obj->t = cylinder_intersect(ray->orig, ray->dir, obj);
	obj->rot = vec_norm(obj->rot);
	if (obj->t > 0 && obj->t < sdl->min_t)
	{
		sdl->min_t = obj->t;
		sdl->clos_obj = i;
	}
}

void	light_data(t_sdl *sdl, char **str)
{
	int i;

	i = -1;
	sdl->light[sdl->light_counter].pos.x = (double)(atoi(str[1]));
	sdl->light[sdl->light_counter].pos.y = (double)(atoi(str[2]));
	sdl->light[sdl->light_counter].pos.z = (double)(atoi(str[3]));
	sdl->light[sdl->light_counter].inten = (double)(atoi(str[4])) / 100;
	if (sdl->light[sdl->light_counter].inten < 0)
		ft_error("Wrong intensity parameter");
	sdl->light_counter++;
	while (++i <= 4)
		free(str[i]);
	free(str);
}

int		shadow_init(t_light *light, t_sdl *sdl)
{
	int		i;
	double	max_t;
	double	t;
	t_vec	dir;

	i = -1;
	t = 0;
	max_t = vec_len(vec_sub(light->pos, light->p));
	dir = vec_norm(vec_sub(light->pos, light->p));
	light->p = vec_sum(light->p, vec_scale(dir, EPS));
	while (++i < sdl->obj_num)
	{
		if (sdl->obj[i].name == SPHERE)
			t = sphere_intersect(light->p, dir, &sdl->obj[i]);
		else if (sdl->obj[i].name == PLANE)
			t = plane_intersect(light->p, dir, &sdl->obj[i]);
		else if (sdl->obj[i].name == CONE)
			t = cone_intersect(light->p, dir, &sdl->obj[i]);
		else if (sdl->obj[i].name == CYLINDER)
			t = cylinder_intersect(light->p, dir, &sdl->obj[i]);
		if (t > 0.00001 && t < max_t)
			return (1);
	}
	return (0);
}

void	get_intensity(t_sdl *sdl, t_light *light, t_vec v, double s)
{
	double	n_dot_l;
	double	r_dot_v;
	double	inten;
	t_vec	l;
	t_vec	r;

	light->new_inten = sdl->ambient;
	inten = 0.0;
	l = vec_norm(vec_sub(light->pos, light->p));
	n_dot_l = vec_dot(light->n, l);
	if (shadow_init(light, sdl) == 0)
		inten = light->inten;
	if (n_dot_l > EPS)
		light->new_inten += inten * (n_dot_l / (vec_len(light->n) *
					vec_len(l)));
	if (s > 0)
	{
		r = vec_scale(light->n, 2);
		r = vec_scale(r, vec_dot(light->n, l));
		r = vec_sub(r, l);
		r_dot_v = vec_dot(r, v);
		if (r_dot_v > EPS)
			light->new_inten += inten * pow((r_dot_v / (vec_len(r) *
							vec_len(v))), s);
	}
}

void	light(t_sdl *sdl, t_ray *ray)
{
	int	i;

	i = 0;
	if (sdl->clos_obj > -1)
	{
		while (i < sdl->light_num)
		{
			sdl->light[i].p = vec_sum(ray->orig, vec_scale(ray->dir, OBJ.t));
			if (OBJ.name == SPHERE)
				sdl->light[i].n = sphere_normal(ray, &OBJ);
			else if (OBJ.name == PLANE)
				sdl->light[i].n = OBJ.rot;
			else if (OBJ.name == CYLINDER)
				sdl->light[i].n = cyl_normal_calc(ray, &OBJ);
			else if (OBJ.name == CONE)
				sdl->light[i].n = cone_normal_calc(ray, &OBJ);
			get_intensity(sdl, &sdl->light[i], vec_scale(ray->dir, -1),
					OBJ.specular);
			i++;
		}
	}
}

void	plane_data(t_sdl *sdl, char **str)
{
	int i;

	i = -1;
	OBJP.pos.x = (double)(atoi(str[1]));
	OBJP.pos.y = (double)(atoi(str[2]));
	OBJP.pos.z = (double)(atoi(str[3]));
	OBJP.rot.x = (double)(atoi(str[4]));
	OBJP.rot.y = (double)(atoi(str[5]));
	OBJP.rot.z = (double)(atoi(str[6]));
	if (atoi(str[7]) < 0 || atoi(str[8]) < 0 || atoi(str[9]) < 0)
		ft_error("Wrong input");
	OBJP.col.rgb[0] = (unsigned char)(atoi(str[7]));
	OBJP.col.rgb[1] = (unsigned char)(atoi(str[8]));
	OBJP.col.rgb[2] = (unsigned char)(atoi(str[9]));
	OBJP.specular = (double)(atoi(str[10]));
	OBJP.name = PLANE;
	sdl->obj_counter++;
	while (++i <= 10)
		free(str[i]);
	free(str);
}

t_vec	plane_normal(t_ray *ray, t_object *obj)
{
	if (vec_dot(ray->dir, obj->rot) < 0)
		return (obj->rot);
	return (vec_scale(obj->rot, -1));
}

double	plane_intersect(t_vec o, t_vec dir, t_object *obj)
{
	double	t;
	double	a;
	double	b;
	t_vec	x;

	x = vec_sub(o, obj->pos);
	a = vec_dot(x, obj->rot);
	b = vec_dot(dir, obj->rot);
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
		return (-1);
	t = -a / b;
	if (t > EPS)
		return (t);
	return (-1);
}

void	plane(t_sdl *sdl, t_ray *ray, int i, t_object *obj)
{
	obj->rot = vec_norm(obj->rot);
	obj->t = plane_intersect(ray->orig, ray->dir, obj);
	if (obj->t > 0 && obj->t < sdl->min_t)
	{
		sdl->min_t = obj->t;
		sdl->clos_obj = i;
	}
}

void	sphere_data(t_sdl *sdl, char **str)
{
	int i;

	i = -1;
	OBJP.pos.x = (double)(atoi(str[1]));
	OBJP.pos.y = (double)(atoi(str[2]));
	OBJP.pos.z = (double)(atoi(str[3]));
	OBJP.r = (double)(atoi(str[4])) / 10;
	if (OBJP.r < 0.1 || atoi(str[5]) < 0 || atoi(str[6]) < 0
		|| atoi(str[7]) < 0)
		ft_error("Wrong input for sphere");
	OBJP.col.rgb[0] = (unsigned char)(atoi(str[5]));
	OBJP.col.rgb[1] = (unsigned char)(atoi(str[6]));
	OBJP.col.rgb[2] = (unsigned char)(atoi(str[7]));
	OBJP.specular = (double)(atoi(str[8]));
	OBJP.name = SPHERE;
	sdl->obj_counter++;
	while (++i <= 8)
		free(str[i]);
	free(str);
}

t_vec	sphere_normal(t_ray *ray, t_object *obj)
{
	t_vec n;

	n = vec_sum(ray->orig, vec_scale(ray->dir, obj->t));
	n = vec_norm(vec_sub(n, obj->pos));
	if (vec_dot(ray->dir, n) > EPS)
		n = vec_scale(n, -1);
	return (n);
}

double	get_t(double a, double b, double d)
{
	double t1;
	double t2;

	t1 = (-b - sqrt(d)) / (2 * a);
	t2 = (-b + sqrt(d)) / (2 * a);
	if ((t1 <= t2 && t1 >= 0) || (t1 >= 0 && t2 < 0))
		return (t1);
	else if ((t2 <= t1 && t2 >= 0) || (t1 < 0 && t2 >= 0))
		return (t2);
	return (-1);
}

double	sphere_intersect(t_vec o, t_vec dir, t_object *obj)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vec	oc;

	oc = vec_sub(o, obj->pos);
	a = vec_dot(dir, dir);
	b = 2 * vec_dot(oc, dir);
	c = vec_dot(oc, oc) - (obj->r * obj->r);
	d = b * b - 4 * a * c;
	if (d < 0)
		return (-1);
	return (get_t(a, b, d));
}

void	sphere(t_sdl *sdl, t_ray *ray, int i, t_object *obj)
{
	obj->t = sphere_intersect(ray->orig, ray->dir, obj);
	if (obj->t > 0 && obj->t < sdl->min_t)
	{
		sdl->min_t = obj->t;
		sdl->clos_obj = i;
	}
}

void	ambient_data(t_sdl *sdl, char **str)
{
	int i;

	i = -1;
	sdl->ambient = (double)(atoi(str[1])) / 100;
	if (sdl->ambient < 0)
		ft_error("Wrong intensity parameter");
	while (++i <= 1)
		free(str[i]);
	free(str);
}

void	split_parse(char **str, t_sdl *sdl)
{
	if (ft_strequ(str[0], "cam:"))
		cam_data(sdl, str);
	else if (ft_strequ(str[0], "sphere:"))
		sphere_data(sdl, str);
	else if (ft_strequ(str[0], "plane:"))
		plane_data(sdl, str);
	else if (ft_strequ(str[0], "cylinder:"))
		cylinder_data(sdl, str);
	else if (ft_strequ(str[0], "cone:"))
		cone_data(sdl, str);
	else if (ft_strequ(str[0], "light:"))
		light_data(sdl, str);
	else if (ft_strequ(str[0], "ambient:"))
		ambient_data(sdl, str);
}

void	ft_parse(char *arg, t_sdl *sdl)
{
	char	*line;
	int		fd;
	int		i;
	char	**spl_res;

	i = 0;
	fd = 0;
	line = NULL;
	sdl->obj_num = 0;
	sdl->light_num = 0;
	sdl->obj_counter = 0;
	sdl->light_counter = 0;
	validation_init(arg, sdl, i, fd);
	sdl->obj = ft_memalloc(sizeof(t_object) * sdl->obj_num);
	sdl->light = ft_memalloc(sizeof(t_light) * sdl->light_num);
	if ((fd = open(arg, O_RDONLY)) < 0)
		ft_error("Can't open the file");
	while ((i = get_next_line(fd, &line)) > 0)
	{
		spl_res = ft_strsplit(line, ' ');
		split_parse(spl_res, sdl);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

void	val_1(char **str, int k)
{
	int i;

	i = 0;
	while (++i <= k)
		if (!str[i] || (atoi(str[i]) == 0 && str[i][0] != '0') ||
				str[k + 1] != NULL || !val_2(str[i]))
			ft_error("Wrong input");
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
	else if (ft_strequ(str[0], "cylinder:"))
		val_1(str, 11);
	else if (ft_strequ(str[0], "cone:"))
		val_1(str, 11);
	else if (ft_strequ(str[0], "light:"))
		val_1(str, 4);
	else if (ft_strequ(str[0], "ambient:"))
		val_1(str, 1);
}

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
	return (0);
}

void	obj_counter(t_sdl *sdl, char **spl_res)
{
	if (ft_strequ(SPL, "sphere:") || ft_strequ(SPL, "plane:") ||
		ft_strequ(SPL, "cylinder:") || ft_strequ(SPL, "cone:"))
		sdl->obj_num++;
	else if (ft_strequ(SPL, "light:"))
		sdl->light_num++;
	else if (ft_strequ(SPL, "cam:"))
		sdl->cam_is++;
}

void	 validation_init(char *arg, t_sdl *sdl, int fd, int i)
{
	char	*line;
	char	**spl_res;

	line = NULL;
	sdl->cam_is = 0;
	if ((fd = open(arg, O_RDONLY)) < 0)
		ft_error("Can't open the file");
	while ((i = get_next_line(fd, &line)) > 0)
	{
		if (line_valid(line) == 0)
			ft_error("Wrong input");
		spl_res = ft_strsplit(line, ' ');
		ft_strdel(&line);
		obj_counter(sdl, spl_res);
		validation(spl_res);
	}
	ft_strdel(&line);
	if (sdl->cam_is != 1)
		ft_error("Have no camera");
	if (sdl->light_num == 0)
		ft_error("Have no light");
	if (sdl->obj_num < 1)
		ft_error("Have no objects");
	close(fd);
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

void	cam_data(t_sdl *sdl, char **str)
{
	int i;

	i = -1;
	sdl->cam.pos.x = (double)(atoi(str[1]));
	sdl->cam.pos.y = (double)(atoi(str[2]));
	sdl->cam.pos.z = (double)(atoi(str[3]));
	sdl->cam.rot.x = (double)(atoi(str[4]));
	sdl->cam.rot.y = (double)(atoi(str[5]));
	sdl->cam.rot.z = (double)(atoi(str[6]));
	while (++i <= 6)
		free(str[i]);
	free(str);
}

void	init_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
		if ((sdl->wind = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_UNDEFINED,
						SDL_WINDOWPOS_UNDEFINED, DWIDTH,
						DHEIGHT, SDL_WINDOW_SHOWN)))
			if ((sdl->rend = SDL_CreateRenderer(sdl->wind, -1,
							SDL_RENDERER_ACCELERATED)))
				return ;
	ft_putendl("Error in init_sdl()");
	exit(0);
}

void	ft_error(char *str)
{
	ft_putendl(str);
	exit(1);
}

int		main(int argc, char **argv)
{
	t_sdl		sdl;
	t_ray		ray;
	SDL_Event	event;

	init_sdl(&sdl);
	ft_parse(argv[1], &sdl);
	if (argc != 2 || !argv[1])
		ft_error("Wrong arguments");
	ray.orig.x = sdl.cam.pos.x;
	ray.orig.y = sdl.cam.pos.y;
	ray.orig.z = sdl.cam.pos.z;
	ray_trace_init(&sdl, &ray);
	SDL_RenderPresent(sdl.rend);
	while (1)
		while (SDL_PollEvent(&event))
			if ((SDL_QUIT == event.type) || (SDL_KEYDOWN == event.type &&
				SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
				exit(0);
	return (0);
}


void	get_dir(double x, double y, t_ray *ray, t_sdl *sdl)
{
	ray->dir.x = x * (V_W / (double)DWIDTH);
	ray->dir.y = y * (V_H / (double)DHEIGHT);
	ray->dir.z = 1.0;
	ray->dir = vec_rot(ray->dir, sdl->cam.rot);
}

void	set_color(t_sdl *sdl, int i, int x, int y)
{
	double	p;
	int		k;

	k = 0;
	p = 0;
	while (k < sdl->light_num)
	{
		if (sdl->light[k].new_inten > 1)
			sdl->light[k].new_inten = 1;
		p += sdl->light[k].new_inten;
		if (p > 1)
			p = 1;
		k++;
	}
	if (i > -1)
	{
		SDL_SetRenderDrawColor(sdl->rend, sdl->obj[i].col.rgb[0] * p,
			sdl->obj[i].col.rgb[1] * p, sdl->obj[i].col.rgb[2] * p, 255);
		SDL_RenderDrawPoint(sdl->rend, x, y);
	}
	else
	{
		SDL_SetRenderDrawColor(sdl->rend, 0, 0, 0, 255);
		SDL_RenderDrawPoint(sdl->rend, x, y);
	}
}



















void	intersection_check(t_ray *ray, t_sdl *sdl, int x, int y)
{
	int	i;

	i = 0;
	sdl->clos_obj = -1;
	sdl->min_t = INFINITY;
	while (i < sdl->obj_num)
	{
		if (sdl->obj[i].name == SPHERE)
			sphere(sdl, ray, i, &sdl->obj[i]);
		else if (sdl->obj[i].name == PLANE)
			plane(sdl, ray, i, &sdl->obj[i]);
		else if (sdl->obj[i].name == CYLINDER)
			cylinder(sdl, ray, i, &sdl->obj[i]);
		else if (sdl->obj[i].name == CONE)
			cone(sdl, ray, i, &sdl->obj[i]);
		i++;
	}
	if (sdl->clos_obj > -1)
		light(sdl, ray);
	set_color(sdl, sdl->clos_obj, x, y);
}

















void	ray_trace_init(t_sdl *sdl, t_ray *ray)
{
	int		x;
	int		y;
	double	n_x;
	double	n_y;

	x = 0;
	while (x <= DWIDTH)
	{
		y = 0;
		n_x = (x + 0.5) / (double)DWIDTH;
		n_x = 2 * n_x - 1;
		while (y <= DHEIGHT)
		{
			n_y = (y + 0.5) / (double)DHEIGHT;
			n_y = 1 - (2 * n_y);
			get_dir(n_x, n_y, ray, sdl);
			intersection_check(ray, sdl, x, y);
			y++;
		}
		x++;
	}
}