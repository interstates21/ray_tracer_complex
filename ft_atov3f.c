#include "inc/rt.h"

static float	ft_atof(char *str)
{
	int		i;
	int		sign;
	float	n;
	float	k;

	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		++i;
	sign = (str[i] == '-' ? -1 : 1);
	if (str[i] == '-' || str[i] == '+')
		++i;
	if (!(str[i] >= '0' && str[i] <= '9') && \
		(str[i] != '.' || !(str[i + 1] >= '0' && str[i + 1] <= '9')))
		return (0);
	n = 0.0;
	while (str[i] >= '0' && str[i] <= '9')
		n = n * 10.0 + (str[i++] - '0');
	if (str[i++] != '.')
		return (n * (float)sign);
	k = 1.0;
	while (str[i] >= '0' && str[i] <= '9' && (k *= 10.0))
		n += ((float)(str[i++] - '0') / k);
	return (n * (float)sign);
}

static int		check_special_symbol(char *s, int i)
{
	if (s[i] == '-')
	{
		if (i >= 1 && (s[i - 1] >= '0' && s[i - 1] <= '9'))
			return (0);
		if (!s[i + 1])
			return (0);
		if (s[i + 1] == ':')
			return (0);
		if ((s[i + 1] == '-' || s[i + 1] == '.'))
			return (0);
	}
	else if (s[i] == '.')
	{
		if (i < 1 || !s[i + 1])
			return (0);
		if (s[i - 1] == ':')
			return (0);
		if (s[i + 1] == '.' || s[i + 1] == ':' || s[i + 1] == '-')
			return (0);
	}
	return (1);
}

static int		check_format(char *s)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] == ':')
		{
			if (i == 0 || !s[i + 1] || (s[i + 1] && s[i + 1] == ':'))
				return (0);
			n++;
		}
		else if (s[i] == '.' || s[i] == '-')
		{
			if (!check_special_symbol(s, i))
				return (0);
		}
		else if ((s[i] < '0' || s[i] > '9'))
			return (0);
		i++;
	}
	if (n != 2)
		return (0);
	return (1);
}

int				ft_atof_check(float *n, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (i == 0 || !str[i + 1] || (str[i + 1] && str[i + 1] == '.'))
				return (0);
		}
		else if ((str[i] < '0' || str[i] > '9'))
			return (0);
		i++;
	}
	*n = ft_atof(str);
	return (1);
}

int				ft_atov3f(t_v3f *v, char *s)
{
	int i;

	if (!check_format(s))
		return (0);
	i = 0;
	v->x = ft_atof(s);
	while (s[++i] != ':')
		continue;
	v->y = ft_atof(s + i + 1);
	while (s[++i] != ':')
		continue;
	v->z = ft_atof(s + i + 1);
	return (1);
}
