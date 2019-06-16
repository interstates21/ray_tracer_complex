#include "rt.h"

void	clean_lists(t_objects *objects, t_lights *lights)
{
	t_lights	*ltmp;
	t_objects	*otmp;

	while (lights)
	{
		ltmp = lights;
		lights = lights->next;
		free(ltmp);
	}
	while (objects)
	{
		otmp = objects;
		objects = objects->next;
		free(otmp);
	}
}

int		str_array_len(char **split)
{
	int			i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int		clean_ok(char *line, char **split)
{
	int			i;

	i = 0;
	while (split[i])
		free(split[i++]);
	if (line)
		free(line);
	if (split)
		free(split);
	return (0);
}

int		clean_err(t_objects *objects,
		t_lights *lights, char *line, char **split)
{
	int			i;

	i = 0;
	while (split[i])
		free(split[i++]);
	if (line)
		free(line);
	if (split)
		free(split);
	clean_lists(objects, lights);
	return (0);
}
