#include "fractol.h"

static void	malloc_error(void)
{
	perror("Malloc Error\n");
	exit(EXIT_FAILURE);
}

static void	data_init(t_fractal *fractal)
{
	fractal->escape_value = 4;
	fractal->iteration_definition = 42;
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	fractal->zoom = 1.0;
}

static void	events_init(t_fractal *fractal)
{
	mlx_hook(fractal->mlx_window,
			KeyPress,
			KeyPressMask,
			key_handler,
			fractal);
	mlx_hook(fractal->mlx_window,
			ButtonPress,
			ButtonPressMask,
			mouse_handler,
			fractal);
	mlx_hook(fractal->mlx_window,
			DestroyNotify,
			StructureNotifyMask,
			close_handler,
			fractal);
	mlx_hook(fractal->mlx_window,
			MotionNotify,
			PointerMotionMask,
			julia_track,
			fractal);
}

void	fractal_init(t_fractal *fractal)
{
	fractal->mlx_connection = mlx_init();
	if (NULL == fractal->mlx_connection)
		malloc_error();
	fractal->mlx_window = mlx_new_window(fractal->mlx_connection, 
												WIDTH, HEIGHT, fractal->name);
	if (NULL == fractal->mlx_window)
	{
		mlx_destroy_display(fractal->mlx_connection);
		free(fractal->mlx_connection);
		malloc_error();
	}

	fractal->image.img_ptr = mlx_new_image(fractal->mlx_connection, WIDTH, HEIGHT);

	if (NULL == fractal->image.img_ptr)
	{
		mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
		mlx_destroy_display(fractal->mlx_connection);
		free(fractal->mlx_connection);
		malloc_error();
	}

	fractal->image.pixels_ptr = mlx_get_data_addr(fractal->image.img_ptr, 
													&fractal->image.bits_per_pixel, 
													&fractal->image.line_length, 
													&fractal->image.endian);

	events_init(fractal);
	data_init(fractal);
}