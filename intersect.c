#include "rt.h"

float		sphere_intersect(t_math math, t_ray *ray)
{
	t_quadratic	q;
	float		t1;
	t_v3f		origin_vector;

	origin_vector = substract(ray->pos, math.c);
	q.a = dot(ray->dir, ray->dir);
	q.b = 2 * dot(ray->dir, origin_vector);
	q.c = dot(origin_vector, origin_vector) - math.r * math.r;
	q.discr = q.b * q.b - 4 * q.a * q.c;
	if (q.discr < 0)
		return (MAX_DIST);
	t1 = (-q.b - sqrt(q.discr)) / (2 * q.a);
	if (t1 > 0 && t1 < MAX_DIST)
	{
		ray->normal = normalize(substract(add(ray->pos,
		mult(ray->dir, t1)), math.c));
		return (t1);
	}
	return (MAX_DIST);
}

float		plane_intersect(t_math math, t_ray *ray)
{
	float		temp;
	float		t;

	math.n = normalize(math.n);
	temp = dot(ray->dir, math.n);
	if (temp == 0.0f)
		return (MAX_DIST);
	t = dot(substract(math.c, ray->pos), math.n) / temp;
	if (t > 0 && t < MAX_DIST)
	{
		ray->normal = math.n;
		return (t);
	}
	return (MAX_DIST);
}

float		cylinder_intersect(t_math math, t_ray *ray)
{
	t_quadratic	q;
	float		t;
	float		d;
	float		d2;
	t_v3f		temp;

	math.n = normalize(math.n);
	temp = substract(ray->pos, math.c);
	d = dot(ray->dir, math.n);
	d2 = dot(temp, math.n);
	q.a = dot(ray->dir, ray->dir) - d * d;
	q.b = 2 * (dot(ray->dir, temp) -
	(d * d2));
	q.c = dot(temp, temp) - (d2 * d2) - (math.r * math.r);
	q.discr = (q.b * q.b) - 4 * q.a * q.c;
	if (q.discr < 0)
		return (MAX_DIST);
	t = (-q.b - sqrt(q.discr)) / (2 * q.a);
	if (t > 0 && t < MAX_DIST)
	{
		ray->normal = calc_cylinder_normal(math, ray, t);
		return (t);
	}
	return (MAX_DIST);
}

float		cone_intersect(t_math math, t_ray *ray)
{
	t_quadratic	q;
	float		t;
	float		k;
	float		d;
	t_v3f		temp;

	math.n = normalize(math.n);
	d = dot(ray->dir, math.n);
	temp = substract(ray->pos, math.c);
	k = tan(math.r);
	k = k * k + 1;
	q.a = dot(ray->dir, ray->dir) - k * d * d;
	q.b = 2 * (dot(ray->dir, temp) - k * d * dot(temp, math.n));
	q.c = dot(temp, temp) - k * pow(dot(temp, math.n), 2);
	q.discr = q.b * q.b - (4 * q.a * q.c);
	if (q.discr <= 0)
		return (MAX_DIST);
	t = (-q.b - sqrt(q.discr)) / (2 * q.a);
	if (t > 0 && t < MAX_DIST)
	{
		ray->normal = calc_cone_normal(math, ray, t);
		return (t);
	}
	return (MAX_DIST);
}

float		choose_intersection(t_objects *objects, t_ray *ray)
{
	if (objects->type == 0)
		return (sphere_intersect(objects->math, ray));
	if (objects->type == 1)
		return (plane_intersect(objects->math, ray));
	if (objects->type == 2)
		return (cylinder_intersect(objects->math, ray));
	return (cone_intersect(objects->math, ray));
}
