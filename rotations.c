#include "inc/rt.h"

static void		rot_z(t_v3f *p, float teta)
{
	float tmp;
	float cos_teta;
	float sin_teta;

	teta *= M_PI / 180.0;
	cos_teta = cos(teta);
	sin_teta = sin(teta);
	tmp = p->x;
	p->x = p->x * cos_teta - p->y * sin_teta;
	p->y = tmp * sin_teta + p->y * cos_teta;
}

static void		rot_y(t_v3f *p, float teta)
{
	float tmp;
	float cos_teta;
	float sin_teta;

	teta *= M_PI / 180.0;
	cos_teta = cos(teta);
	sin_teta = sin(teta);
	tmp = p->z;
	p->z = p->z * cos_teta + p->x * sin_teta;
	p->x = p->x * cos_teta - tmp * sin_teta;
}

static void		rot_x(t_v3f *p, float teta)
{
	float tmp;
	float cos_teta;
	float sin_teta;

	teta *= M_PI / 180.0;
	cos_teta = cos(teta);
	sin_teta = sin(teta);
	tmp = p->y;
	p->y = p->y * cos_teta - p->z * sin_teta;
	p->z = tmp * sin_teta + p->z * cos_teta;
}

void			rotations(t_v3f *p, t_v3f quter)
{
	rot_x(p, quter.x);
	rot_y(p, quter.y);
	rot_z(p, quter.z);
}
