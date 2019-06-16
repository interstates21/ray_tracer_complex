#include "rt.h"

static int		is_valid_file(char *filename)
{
	int			fd;
	char		buff[10];

	if (!(fd = open(filename, O_RDONLY)))
		return (p_err("Open file failed"));
	if (read(fd, buff, 10) < 10)
		return (0);
	return (1);
}


// static int		on_update_frame()
// {
// 	mlx_hook(mlx->win,
// 	HOOK_PRESS_KEY, HOOK_RESET_KEY, listen_controls, &controls);
// 	start_threads(cam, objects, lights, mlx);
// 	clean_lists(objects, lights);
// 	mlx_put_image_to_window(mlx->init, mlx->win, mlx->img, 0, 0);
// }

static t_scene	create_scene(t_lights *lights, t_objects *objects, t_cam cam, t_mlx *mlx) {
	t_scene scene;

	scene.lights = lights;
	scene.objects = objects;
	scene.cam = cam;
	scene.mlx = mlx;

	return (scene);
}

static int		initial_frame(t_mlx *mlx, char *name)
{
	t_lights	*lights;
	t_objects	*objects;
	t_cam		cam;
	t_scene		scene;
	int			fd;

	lights = NULL;
	objects = NULL;
	cam.is_set = 0;
	if (!(fd = open(name, O_RDONLY)))
		return (p_err("Open file failed"));
	if (!read_scene(fd, &lights, &objects, &cam))
		return (0);
	if (!lights || !objects || !cam.is_set)
		return (p_err("Scene: must contain at least one light, obj and cam"));
	scene = create_scene(lights, objects, cam, mlx);
	start_threads(scene);
	clean_lists(objects, lights);
	mlx_put_image_to_window(mlx->init, mlx->win, mlx->img, 0, 0);
	return (1);
}


int				main(int argc, char **argv)
{
	t_mlx		mlx;

	if (argc != 2)
		return (print_instructions());
	if (!is_valid_file(argv[1]))
		return (print_instructions());
	if (!(mlx.init = mlx_init()))
		return (p_err("mlx failed"));
	if (!(mlx.win = mlx_new_window(mlx.init, WIDTH, HEIGHT, WIN_NAME)))
		return (p_err("mlx failed"));
	if (!(mlx.img = mlx_new_image(mlx.init, WIDTH, HEIGHT)))
		return (p_err("mlx failed"));
	if (!(mlx.img_string = mlx_get_data_addr(mlx.img,
		&mlx.bpp, &mlx.line_size, &mlx.endian)))
		return (p_err("mlx failed"));
	if (!initial_frame(&mlx, argv[1]))
		return (0);
	mlx_hook(mlx.win,
	HOOK_RED_CROSS_IN, HOOK_RED_CROSS_OUT, my_exit, NULL);
	mlx_hook(mlx.win,
	HOOK_PRESS_KEY, HOOK_RESET_KEY, listen_key_exit, NULL);
	mlx_loop(mlx.init);
	return (0);
}
