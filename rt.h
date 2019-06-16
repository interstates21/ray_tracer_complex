
#ifndef RTV1_H
# define RTV1_H
# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>
# include <pthread.h>

# define WIN_NAME "Raytracer"
# define MAX(a,b) ((a < b) ? b : a)
# define CLAMP(x, a, b) (((x) > (b)) ? (b) : (((x) < (a)) ? (a) : (x)))
# define HOOK_PRESS_KEY 2
# define HOOK_RESET_KEY 5
# define HOOK_RED_CROSS_IN 17
# define HOOK_RED_CROSS_OUT 0
# define KEY_EXIT 53
# define WIDTH 1300
# define HEIGHT 600
# define LIMIT_PIXEL_WIN_EDGE 55
# define N_THREADS 8
# define MAX_DIST 1000
# define EPSILON 0.001f
# define EXPOSURE 1
# define COL_DISPL 0x222222

typedef struct	s_v3f
{
	float		x;
	float		y;
	float		z;
}				t_v3f;

typedef struct	s_rgb
{
	int			red;
	int			green;
	int			blue;
}				t_rgb;

typedef struct	s_d_shader
{
	float		red;
	float		green;
	float		blue;
	float		specular;
	float		diffuse;
	float		ambient;
}				t_d_shader;

typedef struct	s_shading
{
	t_rgb		color;
	t_v3f		hit;
	t_v3f		normal;
	float		kd;
	float		ka;
	float		ks;
	float		gs;
}				t_shading;

typedef struct	s_quadratic
{
	float		a;
	float		b;
	float		c;
	float		discr;
}				t_quadratic;

typedef struct	s_math
{
	t_v3f		c;
	t_v3f		transf;
	t_v3f		n;
	float		r;
}				t_math;

typedef struct	s_cam
{
	t_v3f		pos;
	t_v3f		look_at;
	t_v3f		up;
	t_v3f		forward;
	t_v3f		right;
	float		fov;
	int			is_set;
}				t_cam;

typedef struct	s_ray
{
	t_v3f		pos;
	t_v3f		dir;
	t_v3f		normal;
}				t_ray;

typedef struct	s_mlx
{
	void		*init;
	void		*win;
	void		*img;
	char		*img_string;
	int			endian;
	int			line_size;
	int			bpp;
}				t_mlx;

typedef struct	s_objects
{
	struct s_objects	*next;
	int					type;
	t_shading			shading;
	t_math				math;
}				t_objects;

typedef struct	s_lights
{
	struct s_lights		*next;
	int					type;
	t_v3f				pos;
}				t_lights;

typedef	struct	s_range
{
	int			min;
	int			max;
}				t_range;

typedef	struct	s_scene
{
	t_lights	*lights;
	t_objects	*objects;
	t_cam		cam;
	t_mlx		*mlx;
}				t_scene;

typedef struct	s_render_data
{
	t_range		range;
	t_objects	*objects;
	t_lights	*lights;
	t_cam		cam;
	char		*img;
}				t_render_data;

void			rotations(t_v3f *p, t_v3f quter);
void			put_pixel_to_img(char **img, int x, int y, t_rgb rgb);
void			start_threads(t_scene scene);
t_v3f			new_v3f(float x, float y, float z);
t_rgb			new_rgb(int red, int green, int blue);
int				print_instructions(void);
int				my_exit(void);
int				listen_key_exit(int keycode);
t_rgb			color_convert(unsigned int c);
float			choose_intersection(t_objects *objects, t_ray *ray);
int				is_zero_vector(t_v3f v);
float			dot(t_v3f a, t_v3f b);
t_v3f			mult(t_v3f a, float scalar);
t_v3f			cross(t_v3f a, t_v3f b);
t_v3f			add(t_v3f a, t_v3f b);
t_v3f			projection(t_v3f a, t_v3f b);
t_v3f			substract(t_v3f a, t_v3f b);
float			mag(t_v3f a);
t_rgb			shader(t_objects *objects, t_lights *lights,
				t_shading shading, t_ray ray);
t_v3f			normalize(t_v3f a);

t_v3f			calc_cylinder_normal(t_math math, t_ray *ray, float t);
t_v3f			calc_cone_normal(t_math math, t_ray *ray, float t);

int				read_scene(int fd, t_lights **lights,
				t_objects **objects, t_cam *cam);
int				str_array_len(char **split);
int				push_back_light(t_lights **begin, t_v3f pos);
int				push_back(t_objects **begin, t_objects data,
				t_v3f k_shade, t_v3f color);

int				parse_objects(t_objects **objects,
				char **split, int *is_obj_set);
int				clean_ok(char *line, char **split);
int				clean_err(t_objects *objects, t_lights *lights,
				char *line, char **split);
int				ft_atov3f(t_v3f *v, char *s);
int				ft_atof_check(float *n, char *str);
int				init_and_validate_vectors(t_objects *data);

int				p_err(char *str);
int				get_next_line(const int fd, char **line);
void			clean_lists(t_objects *objects, t_lights *lights);

#endif
