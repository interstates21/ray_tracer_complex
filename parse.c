#include "inc/rt.h"

int				init_and_validate_vectors(t_objects *data)
{
	if (data->type != 1 && data->math.r < EPSILON)
		return (0);
	data->math.n = new_v3f(0, 1.0f, 0);
	if (is_zero_vector(data->math.c))
		data->math.c = new_v3f(-0.1f, -0.1f, -0.1f);
	data->math.r = CLAMP(data->math.r, 0.2f, 200.0f);
	data->shading.gs = CLAMP(data->shading.gs, 0, 500.0f);
	rotations(&data->math.n, data->math.transf);
	return (1);
}

static int		parse_light(t_lights **lights, char **split)
{
	t_v3f	pos;

	if (str_array_len(split) != 2)
		return (p_err("Scene: light must have 2 keys"));
	if (!ft_atov3f(&pos, split[1]))
		return (p_err("Scene: light invalid format"));
	if (!push_back_light(lights, pos))
		return (0);
	return (1);
}

static int		parse_cam(t_cam *cam, char **split)
{
	t_v3f	rot;

	if (cam->is_set)
		return (p_err("More than one cam in the scene"));
	if (str_array_len(split) != 3)
		return (p_err("Scene: cam must have 3 keys"));
	if (!ft_atov3f(&cam->pos, split[1]))
		return (p_err("Scene: cam invalid format"));
	if (!ft_atov3f(&rot, split[2]))
		return (p_err("Scene: cam invalid format"));
	cam->look_at = new_v3f(0, 0, 1.0f);
	cam->fov = 30.0f * M_PI / 180.0f;
	cam->forward = normalize(substract(cam->look_at, cam->pos));
	cam->right = normalize(cross(cam->forward, new_v3f(0, 1.0f, 0)));
	cam->up = cross(cam->right, cam->forward);
	rotations(&cam->right, rot);
	rotations(&cam->up, rot);
	rotations(&cam->forward, rot);
	cam->is_set = 1;
	return (1);
}

int				read_scene(int fd, t_lights **lights,
							t_objects **objects, t_cam *cam)
{
	char	*line;
	char	**split;
	int		is_obj_set;

	is_obj_set = 0;
	while (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, '|');
		if (!parse_objects(objects, split, &is_obj_set))
			return (clean_err(*objects, *lights, line, split));
		else if (ft_strequ(split[0], "light"))
		{
			if (!parse_light(lights, split))
				return (clean_err(*objects, *lights, line, split));
		}
		else if (ft_strequ(split[0], "camera"))
		{
			if (!parse_cam(cam, split))
				return (clean_err(*objects, *lights, line, split));
		}
		else if (!is_obj_set)
			return (clean_err(*objects, *lights, line, split));
		clean_ok(line, split);
	}
	return (1);
}
