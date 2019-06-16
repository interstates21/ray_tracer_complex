#include    "inc/rt.h"
#define     ROT_SPEED 5

int			listen_controls(int keycode, t_controls *controls)
{
    // SET ROTATION IN DEGREES
	if (keycode == K_LEFT)
        controls->cam_rot_controls.y -= ROT_SPEED;
    if (keycode == K_RIGHT)
        controls->cam_rot_controls.y += ROT_SPEED;
	return (0);
}

t_controls	set_initial_controls(void) {
	t_controls controls;
	
	controls.cam_rot_controls = new_v3f(0, 0, 0);

	return (controls);
}

void         apply_controls(t_controls *controls, t_scene *scene)
{
    // ROTATE CAM AROUND Y
	rotations(&(scene->cam.forward), controls->cam_rot_controls);
    rotations(&(scene->cam.right), controls->cam_rot_controls);
    // rotations(&(scene->cam.up), controls->cam_rot_controls);
}