#include "mlx/mlx.h"
#include "fractol.h"
#include "keys.h"
#include <stdio.h>
#include <stdlib.h>


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int argb(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
	int val;

	val = 0;
	val += a;
	val <<= 8;
	val += b;
	val <<= 8;
	val += c;
	val <<= 8;
	val += d;
	return (val);
}
int	close(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(EXIT_SUCCESS);
	}
	else 
	{
		printf("%p\n", vars);
	}
	return (0);
}
int mandelbrotEscapeIterations(double real, double imag, int maxIter) {
    double zReal = 0.0;
    double zImag = 0.0;
    unsigned int iter = 0;

    while (iter < maxIter) {
        double zRealNew = zReal * zReal - zImag * zImag + real;
        double zImagNew = 2 * zReal * zImag + imag;
        zReal = zRealNew;
        zImag = zImagNew;
        // Check if the magnitude of the complex number exceeds 2 (escape radius)
        if ((zReal * zReal + zImag * zImag) > 4) {
            break;
        }
        iter++;
    }

    return iter;
}

double x_pixel(int x, double x_min, double x_step)
{
	return (x_min + x * x_step);
}

double y_pixel(int y, double y_max, double y_step)
{
	return ( y_max - y * y_step);
}
void zoom(float zoom, t_set *set)
{
	set->y_max = set->y_max * zoom; 
	set->y_min = set->y_min * zoom; 
	set->x_max = set->x_max * zoom; 
	set->x_min = set->x_min * zoom; 
	set->x_step = set->x_step * zoom;
	set->y_step = set->y_step * zoom;
}
void draw_screen(t_args *args, t_set *set, t_data *img)
{

	int i_y = 0;
	int i_x = 0;
	double real;
	double irreal;
	unsigned char red;
	while (i_y < args->high)
	{
		i_x = 0;
		while (i_x < args->width)
		{
			real = x_pixel(i_x, set->x_min, set->x_step);
			irreal = y_pixel(i_y, set->y_max, set->x_step);
			red = mandelbrotEscapeIterations(real, irreal, 255) & 0xFF;
			my_mlx_pixel_put(img, i_x, i_y, argb(0, (433 - red * 20)%255, (red * 20) % 255, (2455 - red * 20)%255));
			//printf("(%f ; %f) - (%i ; %i)\n",real, irreal,i_x,i_y);
			i_x++;
		}
		i_y++;
	}
}
int	mouse_hook(int keycode,int x, int y, t_zoom *zoom_data)
{
	if (keycode == MOUSE_WHEEL_DOWN)
	{
		zoom(0.9, zoom_data->set);
		draw_screen(zoom_data->args, zoom_data->set, zoom_data->img);
		mlx_put_image_to_window(zoom_data->vars->mlx, zoom_data->vars->win, zoom_data->img->img, 0, 0);
	}
	return (0);
}
int	main(void)
{
	t_zoom zoom_data;
	t_vars  vars;
	t_data	img;
	t_set set;
	t_args args;

	zoom_data.args = &args;
	zoom_data.img = &img;
	zoom_data.set = &set;
	zoom_data.vars = &vars;

	args.high = 1000;
	args.width = 1000;
	set.y_max = 2.0;
	set.y_min = -2.0;
	set.x_max = 2.0;
	set.x_min = -2.0;
	set.x_step = (set.x_max - set.x_min) / (args.width - 1.0);
	set.y_step = (set.y_max - set.y_min) / (args.high - 1.0);
	printf("%f\n",zoom_data.set->x_max);

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, args.high, args.width, "Hello world!");
	img.img = mlx_new_image(vars.mlx, args.high, args.width);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	//test
	draw_screen(&args, &set, &img);
	//fin test
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);

	mlx_hook(vars.win, 2, 1L<<0, close, &vars); //close windows
	mlx_mouse_hook(vars.win, mouse_hook, &zoom_data);
	mlx_loop(vars.mlx);
}
