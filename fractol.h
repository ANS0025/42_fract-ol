#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "mlx/mlx.h"
# include "libft/libft.h"

#define ERROR_MESSAGE "Please enter \n\t\"./fractol mandelbrot\" or \n\t\"./fractol julia <value_1> <value_2>\"\n"
#define WIDTH	800
#define	HEIGHT	800

// Colors
#define BLACK       0x000000  // RGB(0, 0, 0)
#define WHITE       0xFFFFFF  // RGB(255, 255, 255)
#define RED         0xFF0000  // RGB(255, 0, 0)
#define GREEN       0x00FF00  // RGB(0, 255, 0)
#define BLUE        0x0000FF  // RGB(0, 0, 255)

// Psychedelic colors
#define MAGENTA_BURST   0xFF00FF  // A vibrant magenta
#define LIME_SHOCK      0xCCFF00  // A blinding lime
#define NEON_ORANGE     0xFF6600  // A blazing neon orange
#define PSYCHEDELIC_PURPLE 0x660066  // A deep purple
#define AQUA_DREAM      0x33CCCC  // A bright turquoise
#define HOT_PINK        0xFF66B2  // As the name suggests!
#define ELECTRIC_BLUE   0x0066FF  // A radiant blue
#define LAVA_RED        0xFF3300  // A bright, molten red

// Complex number
typedef struct s_complex
{
	double	x; // real part
	double	y; // imaginary part
}	t_complex;

// Image
typedef struct s_image
{
	void	*img_ptr; // pointer to image struct
	char	*pixels_ptr; // points to the actual pixel
	int		bits_per_pixel; 
	int		line_length;
	int		endian;
}	t_image;

// Fractal 
typedef struct s_fractal
{
	// Fractal name
	char	*name;
	// MLX
	void	*mlx_connection;
	void	*mlx_window;
	// Image
	t_image	image;
	// Hooks member variables
	double	escape_value;
	int	iteration_definition;
	double shift_x;
	double shift_y;
	double zoom;
	double julia_x;
	double julia_y;
}	t_fractal;

double		atodbl(char *str);
void		fractal_init(t_fractal *fractal);
void		fractal_render(t_fractal *fractal);
double		map(double unscaled_num, double new_min, double new_max, double old_min, double old_max);
t_complex   sum_complex(t_complex z1, t_complex z2);
t_complex   square_complex(t_complex z);
int			key_handler(int keysym, t_fractal *fractal);
int			close_handler(t_fractal *fractal);
int			mouse_handler(int button, int x, int y, t_fractal *fractal);
int			julia_track(int x, int y, t_fractal *fractal);


#endif