#include "rt.h"

static t_shading	save_sh_d(t_shading obj_shading,
						t_v3f n, float *t_min, float t)
{
	t_shading sh;

	sh = obj_shading;
	sh.normal = n;
	*t_min = t;
	return (sh);
}

static t_rgb		trace_ray(t_render_data *data, t_ray ray)
{
	float		tmin;
	float		t;
	t_objects	*objects;
	t_shading	shading;

	objects = data->objects;
	ray.pos = data->cam.pos;
	tmin = MAX_DIST;
	while (objects)
	{
		t = choose_intersection(objects, &ray);
		if (t > EPSILON && t < MAX_DIST)
		{
			if (tmin > t)
				shading = save_sh_d(objects->shading, ray.normal, &tmin, t);
		}
		objects = objects->next;
	}
	if (tmin < EPSILON || tmin >= MAX_DIST)
		return (new_rgb(0, 0, 0));
	shading.hit = add(ray.pos, mult(ray.dir, tmin));
	if (dot(ray.dir, shading.normal) > 0)
		shading.normal = mult(shading.normal, -1);
	return (shader(data->objects, data->lights, shading, ray));
}

static t_ray		generate_ray(t_cam cam, int x, int y)
{
	t_ray	ray;
	float	x_cam_space;
	float	y_cam_space;
	float	h_plane;
	float	w_plane;

	x_cam_space = (2.0f * x) / WIDTH - 1.0;
	y_cam_space = (-2.0f * y) / HEIGHT + 1.0;
	h_plane = tan(cam.fov);
	w_plane = h_plane * WIDTH / HEIGHT;
	ray.dir.x = w_plane * x_cam_space * cam.right.x
	+ h_plane * y_cam_space * cam.up.x + cam.forward.x;
	ray.dir.y = w_plane * x_cam_space * cam.right.y
	+ h_plane * y_cam_space * cam.up.y + cam.forward.y;
	ray.dir.z = w_plane * x_cam_space * cam.right.z
	+ h_plane * y_cam_space * cam.up.z + cam.forward.z;
	ray.dir = normalize(ray.dir);
	return (ray);
}

static void			*render(void *ptr)
{
	t_render_data	*data;
	t_ray			ray;
	int				x;
	int				y;

	data = (t_render_data*)ptr;
	y = 0;
	while (y < HEIGHT)
	{
		x = data->range.min;
		while (x < data->range.max)
		{
			ray = generate_ray(data->cam, x, y);
			put_pixel_to_img(&(data->img), x, y, trace_ray(data, ray));
			x++;
		}
		y++;
	}
	pthread_exit(0);
}

void				start_threads(t_scene scene)
{
	pthread_t		threads[N_THREADS];
	t_render_data	data[N_THREADS];
	int				i;

	i = 0;
	while (i < N_THREADS)
	{
		data[i].range.min = i * (WIDTH / N_THREADS);
		data[i].range.max = (i + 1) * (WIDTH / N_THREADS);
		data[i].lights = scene.lights;
		data[i].objects = scene.objects;
		data[i].cam = scene.cam;
		data[i].img = scene.mlx->img_string;
		pthread_create(&threads[i], NULL, render, &data[i]);
		i++;
	}
	i = 0;
	while (i < N_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
