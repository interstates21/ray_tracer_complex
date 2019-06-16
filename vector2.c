#include "inc/rt.h"

float	dot(t_v3f a, t_v3f b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_v3f	cross(t_v3f a, t_v3f b)
{
	t_v3f c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

float	mag(t_v3f a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_v3f	normalize(t_v3f a)
{
	t_v3f	c;
	float	l;

	l = mag(a);
	c.x = a.x / l;
	c.y = a.y / l;
	c.z = a.z / l;
	return (c);
}

t_v3f	projection(t_v3f a, t_v3f b)
{
	t_v3f		proj;
	float		temp;

	temp = dot(a, b) / dot(b, b);
	proj = mult(b, temp);
	return (proj);
}
