#include "rt.h"

static t_lights			*node_create_light(t_v3f pos)
{
	t_lights *obj;

	if (!(obj = (t_lights*)malloc(sizeof(t_lights))))
		return (NULL);
	obj->pos = pos;
	obj->next = NULL;
	return (obj);
}

static t_objects		*node_create(t_objects data, t_v3f k_shade, t_v3f color)
{
	t_objects *obj;

	if (!(obj = (t_objects*)malloc(sizeof(t_objects))))
		return (NULL);
	obj->next = NULL;
	if (!init_and_validate_vectors(&data))
		return (NULL);
	obj->type = data.type;
	obj->math = data.math;
	obj->shading.ka = CLAMP(k_shade.x, 0.0f, 1.0f);
	obj->shading.kd = CLAMP(k_shade.y, 0.0f, 1.0f);
	obj->shading.ks = CLAMP(k_shade.z, 0.0f, 1.0f);
	obj->shading.gs = data.shading.gs;
	obj->shading.color.red = (int)(CLAMP(color.x, 0, 255));
	obj->shading.color.green = (int)(CLAMP(color.y, 0, 255));
	obj->shading.color.blue = (int)(CLAMP(color.z, 0, 255));
	return (obj);
}

int						push_back_light(t_lights **begin, t_v3f pos)
{
	t_lights *obj;

	if (!(*begin))
	{
		if (!(*begin = node_create_light(pos)))
			return (0);
		return (1);
	}
	obj = *begin;
	while (obj->next)
		obj = obj->next;
	if (!(obj->next = node_create_light(pos)))
		return (0);
	return (1);
}

int						push_back(t_objects **begin, t_objects data,
									t_v3f k_shade, t_v3f color)
{
	t_objects *obj;

	if (!(*begin))
	{
		if (!(*begin = node_create(data, k_shade, color)))
			return (0);
		return (1);
	}
	obj = *begin;
	while (obj->next)
		obj = obj->next;
	if (!(obj->next = node_create(data, k_shade, color)))
		return (0);
	return (1);
}
