#include "inc/rt.h"

int		my_exit(void)
{
	exit(0);
	return (0);
}

int		p_err(char *str)
{
	ft_putendl(str);
	return (0);
}

int		print_instructions(void)
{
	ft_putstr("USAGE: ./RTv1 [SCENE_FILE]\n");
	ft_putstr("SCENE SCRIPTING LANGUAGE:\n");
	ft_putstr("sphere  |[X]:[Y]:[Z]|[RADIUS]");
	ft_putstr("|[KA]:[KD]:[KS]|[GS]|[R]:[G]:[B]\n");
	ft_putstr("plane   |[X]:[Y]:[Z]|[ROT_X]:[ROT_Y]:[ROT_Z]");
	ft_putstr("|[KA]:[KD]:[KS]|[GS]|[R]:[G]:[B]\n");
	ft_putstr("cylinder|[X]:[Y]:[Z]|[RADIUS]|");
	ft_putstr("[ROT_X]:[ROT_Y]:[ROT_Z]|[KA]:[KD]:[KS]|[GS]|[R]:[G]:[B]\n");
	ft_putstr("cone    |[X]:[Y]:[Z]|[RADIUS]|[ROT_X]:[ROT_Y]:[ROT_Z]|");
	ft_putstr("[KA]:[KD]:[KS]|[GS]|[R]:[G]:[B]\n");
	ft_putendl("camera  |[X]:[Y]:[Z]|[ROT_X]:[ROT_Y]:[ROT_Z]");
	ft_putendl("light   |[X]:[Y]:[Z]");
	ft_putendl("*there must be at least one cam, one light and one primitive.");
	ft_putendl("*KA - K AMBIENT - (0.0f - 1.0f)");
	ft_putendl("*KD - K DIFFUSE - (0.0f - 1.0f)");
	ft_putendl("*KS - K SPECULAR - (0.0f - 1.0f)");
	ft_putendl("*GS - GAMMA INTERPOLATION FOR SPECULAR - (0 - 500)");
	ft_putendl("*RGB - COLOR (0 - 255)");
	return (0);
}
