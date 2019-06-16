#include "inc/rt.h"

static int	parse_sphere(t_objects **objects, char **split)
{
	t_objects	data;
	t_v3f		k_shade;
	t_v3f		color;

	data.type = 0;
	if (str_array_len(split) != 6)
		return (p_err("Scene: sphere must have 6 keys"));
	if (!ft_atov3f(&data.math.c, split[1]))
		return (p_err("Scene: sphere invalid format"));
	if (!ft_atof_check(&data.math.r, split[2]))
		return (p_err("Scene: sphere invalid format"));
	if (!ft_atov3f(&k_shade, split[3]))
		return (p_err("Scene: sphere invalid format"));
	if (!ft_atof_check(&data.shading.gs, split[4]))
		return (p_err("Scene: sphere invalid format"));
	if (!ft_atov3f(&color, split[5]))
		return (p_err("Scene: sphere invalid format"));
	if (!push_back(objects, data, k_shade, color))
		return (p_err("Scene: sphere invalid format"));
	return (1);
}

static int	parse_plane(t_objects **objects, char **split)
{
	t_objects	data;
	t_v3f		k_shade;
	t_v3f		color;

	data.type = 1;
	if (str_array_len(split) != 6)
		return (p_err("Scene: plane must have 6 keys"));
	if (!ft_atov3f(&data.math.c, split[1]))
		return (p_err("Scene: plane invalid format"));
	if (!ft_atov3f(&data.math.transf, split[2]))
		return (p_err("Scene: plane invalid format"));
	if (!ft_atov3f(&k_shade, split[3]))
		return (p_err("Scene: plane invalid format"));
	if (!ft_atof_check(&data.shading.gs, split[4]))
		return (p_err("Scene: plane invalid format"));
	if (!ft_atov3f(&color, split[5]))
		return (p_err("Scene: plane invalid format"));
	if (!push_back(objects, data, k_shade, color))
		return (p_err("Scene: plane invalid format"));
	return (1);
}

static int	parse_cylinder(t_objects **objects, char **split)
{
	t_objects	data;
	t_v3f		k_shade;
	t_v3f		color;

	data.type = 2;
	if (str_array_len(split) != 7)
		return (p_err("Scene: cylinder must have 7 keys"));
	if (!ft_atov3f(&data.math.c, split[1]))
		return (p_err("Scene: cyl invalid format"));
	if (!ft_atof_check(&data.math.r, split[2]))
		return (p_err("Scene: cyl invalid format"));
	if (!ft_atov3f(&data.math.transf, split[3]))
		return (p_err("Scene: cyl invalid format"));
	if (!ft_atov3f(&k_shade, split[4]))
		return (p_err("Scene: cyl invalid format"));
	if (!ft_atof_check(&data.shading.gs, split[5]))
		return (p_err("Scene: cyl invalid format"));
	if (!ft_atov3f(&color, split[6]))
		return (p_err("Scene: cyl invalid format"));
	if (!push_back(objects, data, k_shade, color))
		return (p_err("Scene: cyl invalid format"));
	return (1);
}

static int	parse_cone(t_objects **objects, char **split)
{
	t_objects	data;
	t_v3f		k_shade;
	t_v3f		color;

	data.type = 3;
	if (str_array_len(split) != 7)
		return (p_err("Scene: cone must have 7 keys"));
	if (!ft_atov3f(&data.math.c, split[1]))
		return (p_err("Scene: cone invalid format"));
	if (!ft_atof_check(&data.math.r, split[2]))
		return (p_err("Scene: cone invalid format"));
	if (!ft_atov3f(&data.math.transf, split[3]))
		return (p_err("Scene: cone invalid format"));
	if (!ft_atov3f(&k_shade, split[4]))
		return (p_err("Scene: cone invalid format"));
	if (!ft_atof_check(&data.shading.gs, split[5]))
		return (p_err("Scene: cone invalid format"));
	if (!ft_atov3f(&color, split[6]))
		return (p_err("Scene: cone invalid format"));
	if (!push_back(objects, data, k_shade, color))
		return (p_err("Scene: cone invalid format"));
	return (1);
}

int			parse_objects(t_objects **objects, char **split, int *is_obj_set)
{
	if (ft_strequ(split[0], "sphere"))
	{
		if (!parse_sphere(objects, split))
			return (0);
		*is_obj_set = 1;
	}
	else if (ft_strequ(split[0], "plane"))
	{
		if (!parse_plane(objects, split))
			return (0);
		*is_obj_set = 1;
	}
	else if (ft_strequ(split[0], "cylinder"))
	{
		if (!parse_cylinder(objects, split))
			return (0);
		*is_obj_set = 1;
	}
	else if (ft_strequ(split[0], "cone"))
	{
		if (!parse_cone(objects, split))
			return (0);
		*is_obj_set = 1;
	}
	return (1);
}
