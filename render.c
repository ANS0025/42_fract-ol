#include "fractol.h"

static void	my_pixel_put(int x, int y, t_image *image ,int color)
{
	int offset;

	offset = (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int *)(image->pixels_ptr + offset) = color;
}

static void	mandel_vs_julia(t_complex *z, t_complex *c, t_fractal *fractal)
{	
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		c->x = fractal->julia_x;
		c->y = fractal->julia_y;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
	}
}

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	// pixel coordinate x && y scaled to fit mandel needs 
	//                                 --> 📏 <--			🕹🕹🕹 🕹
	z.x = (map(x, -2, +2, 0, WIDTH) * fractal->zoom) + fractal->shift_x;
	z.y = (map(y, +2, -2, 0, HEIGHT) * fractal->zoom) + fractal->shift_y;


	mandel_vs_julia(&z, &c, fractal);


	// How many times you want to iterate z^2 + c
	//	to check if the point escaped?
	while (i < fractal->iteration_definition)
	{
		// actual z^2 + c	
		// z = z^2 + c
		z = sum_complex(square_complex(z), c);
		
		// Is the value escaped???
		// if hypotenuse > 2 i assume the point has escaped
		if ((z.x * z.x) + (z.y * z.y) > fractal->escape_value)
		{
			color = map(i, BLACK, WHITE, 0, fractal->iteration_definition);
			my_pixel_put(x, y, &fractal->image, color);
			return ;
		}
		++i;	
	}
	// We are in MANDELBROT given the iterations made
	my_pixel_put(x, y, &fractal->image, WHITE);
}

void	fractal_render(t_fractal *fractal)
{
	int x;
	int y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			handle_pixel(x, y, fractal);
		}
	}
	mlx_put_image_to_window(fractal->mlx_connection, 
							fractal->mlx_window, 
							fractal->image.img_ptr, 
							0, 0);
}