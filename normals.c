#include "rt.h"

t_v3f		calc_cylinder_normal(t_math math, t_ray *ray, float t)
{
	t_v3f	hit;
	t_v3f	proj;
	t_v3f	normal;

	hit = add(ray->pos, mult(ray->dir, t));
	normal = substract(hit, math.c);
	proj = projection(normal, math.n);
	normal = normalize(mult(substract(normal, proj), -1));
	return (normal);
}

t_v3f		calc_cone_normal(t_math math, t_ray *ray, float t)
{
	t_v3f	hit;
	t_v3f	proj;
	t_v3f	normal;
	float	tan_teta;

	tan_teta = tan(math.r);
	hit = add(ray->pos, mult(ray->dir, t));
	normal = substract(hit, math.c);
	proj = projection(normal, math.n);
	proj = mult(proj, (1 + tan_teta * tan_teta));
	normal = normalize(mult(substract(normal, proj), -1));
	return (normal);
}
