#include "inc/rt.h"

int			listen_key_exit(int keycode)
{
	if (keycode == KEY_EXIT)
		return (my_exit());
	return (0);
}

t_rgb		new_rgb(int red, int green, int blue)
{
	t_rgb col;

	red = CLAMP(red, 2, 254);
	blue = CLAMP(blue, 2, 254);
	green = CLAMP(green, 2, 254);
	col.red = red;
	col.blue = blue;
	col.green = green;
	return (col);
}

t_rgb		color_convert(unsigned int c)
{
	t_rgb rgb;

	rgb.red = (c >> 16) & 255;
	rgb.green = (c >> 8) & 255;
	rgb.blue = c & 255;
	return (rgb);
}

void		put_pixel_to_img(char **img, int x, int y, t_rgb rgb)
{
	if (x < LIMIT_PIXEL_WIN_EDGE || x > WIDTH - LIMIT_PIXEL_WIN_EDGE - 1
	|| y < LIMIT_PIXEL_WIN_EDGE || y > HEIGHT - LIMIT_PIXEL_WIN_EDGE - 1)
		return ;
	(*img)[(x * 4) + (y * 4 * WIDTH)] = rgb.blue;
	(*img)[(x * 4) + (y * 4 * WIDTH) + 1] = rgb.green;
	(*img)[(x * 4) + (y * 4 * WIDTH) + 2] = rgb.red;
}
