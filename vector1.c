#include "inc/rt.h"

t_v3f	new_v3f(float x, float y, float z)
{
	t_v3f c;

	c.x = x;
	c.y = y;
	c.z = z;
	return (c);
}

t_v3f	add(t_v3f a, t_v3f b)
{
	t_v3f c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_v3f	substract(t_v3f a, t_v3f b)
{
	t_v3f c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

t_v3f	mult(t_v3f a, float scalar)
{
	t_v3f c;

	c.x = a.x * scalar;
	c.y = a.y * scalar;
	c.z = a.z * scalar;
	return (c);
}

int		is_zero_vector(t_v3f v)
{
	return (!v.x && !v.y && !v.z);
}
