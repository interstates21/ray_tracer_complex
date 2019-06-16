#include "inc/rt.h"

t_rgb	color_mult(t_rgb b, float a)
{
	t_rgb c;

	c.red = b.red * a;
	c.green = b.green * a;
	c.blue = b.blue * a;

	return (c);
}

t_rgb	color_interpolate(t_rgb b, t_rgb a, float k1)
{
	t_rgb c;

	c.red = (k1 * b.red) + (1 - k1) * a.red;
	c.green = (k1 * b.green) + (1 - k1) * a.green;
	c.blue = (k1 * b.blue) + (1 - k1) * a.blue;

	return (c);
}
