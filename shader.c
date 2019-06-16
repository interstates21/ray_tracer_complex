#include "inc/rt.h"

static float		trace_shadow_ray(t_objects *objects,
							t_v3f hit, t_v3f lvect)
{
	float		t;
	float		tmin;
	t_ray		ray;
	t_objects	*lst;

	if (!objects)
		return (0);
	ray.pos = hit;
	ray.dir = lvect;
	lst = objects;
	tmin = MAX_DIST;
	while (lst)
	{
		t = choose_intersection(lst, &ray);
		if (tmin > t)
			tmin = t;
		lst = lst->next;
	}
	return (tmin);
}

static t_rgb		normalize_color(t_d_shader shader, t_rgb c)
{
	shader.red = (c.red / 255.0f)
	* (shader.diffuse + shader.ambient) + shader.specular;
	shader.green = (c.green / 255.0f)
	* (shader.diffuse + shader.ambient) + shader.specular;
	shader.blue = (c.blue / 255.0f)
	* (shader.diffuse + shader.ambient) + shader.specular;
	shader.red =
	CLAMP((1.0f - exp(shader.red * -(EXPOSURE))), 0.0f, 1.0f);
	shader.green =
	CLAMP((1.0f - exp(shader.green * -(EXPOSURE))), 0.0f, 1.0f);
	shader.blue =
	CLAMP((1.0f - exp(shader.blue * -(EXPOSURE))), 0.0f, 1.0f);
	return (new_rgb((shader.red * 255),
			(shader.green * 255), (shader.blue * 255)));
}

static	float		calc_specular(t_shading shading, t_v3f cam, t_v3f light)
{
	t_v3f			splusl;
	t_v3f			svect;
	t_v3f			lvect;
	float			cos_teta;

	svect = normalize(substract(cam, shading.hit));
	lvect = normalize(substract(light, shading.hit));
	splusl = normalize(add(svect, lvect));
	cos_teta = pow(dot(splusl, shading.normal), (int)shading.gs);
	return (shading.ks * cos_teta);
}

static float		calc_diffuce(t_objects *objects,
						t_shading shading, t_v3f light, int *is_shadow)
{
	t_v3f			lvect;
	float			ldist;
	float			cos_teta;
	float			t;

	*is_shadow = 0;
	lvect = substract(light, shading.hit);
	ldist = mag(lvect);
	lvect = normalize(lvect);
	cos_teta = dot(lvect, shading.normal);
	if (cos_teta < 0)
		return (0);
	t = trace_shadow_ray(objects, shading.hit, lvect);
	if (t < ldist - EPSILON && t > EPSILON)
	{
		*is_shadow = 1;
		return (0);
	}
	return (shading.kd * cos_teta);
}

t_rgb				shader(t_objects *objects,
						t_lights *lights, t_shading shading, t_ray ray)
{
	t_d_shader		d_shader;
	t_lights		*lst;
	float			diffuse;
	int				is_shadow;

	shading.hit = add(shading.hit, mult(shading.normal, EPSILON));
	d_shader.diffuse = 0;
	d_shader.specular = 0;
	d_shader.ambient = shading.ka;
	lst = lights;
	while (lst)
	{
		diffuse = calc_diffuce(objects, shading, lst->pos, &is_shadow);
		if (!is_shadow)
			d_shader.specular += (calc_specular(shading, ray.pos, lst->pos));
		d_shader.diffuse += (diffuse);
		lst = lst->next;
	}
	return (normalize_color(d_shader, shading.color));
}
