#include "fractol.h"
#include "keys.h"
#include "mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
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
int close(int keycode, t_vars *vars)
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
int mandelbrotEscapeIterations(double real, double imag, int maxIter)
{
	double       zReal = 0.0;
	double       zImag = 0.0;
	unsigned int iter = 0;
	double       zRealNew;
	double       zImagNew;
	while (iter < maxIter)
	{
		zRealNew = zReal * zReal - zImag * zImag + real;
		zImagNew = 2 * zReal * zImag + imag;
		zReal = zRealNew;
		zImag = zImagNew;
		// Check if the magnitude of the complex number exceeds 2 (escape radius)
		if ((zReal * zReal + zImag * zImag) > 4)
		{
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
	return (y_max - y * y_step);
}
void zoom(float zoom, t_set *set, int x, int y)
{
	double real;
	double irreal;

	real = x_pixel(x, set->x_min, set->x_step);
	irreal = y_pixel(y, set->y_max, set->y_step);
	set->x_step = set->x_step * zoom;
	set->y_step = set->y_step * zoom;
	set->y_max = irreal + y * set->y_step;
	set->y_min = irreal - (1000 - y) * set->y_step; // change 1000 for high
	set->x_min = real - x * set->x_step;
	set->x_max = real + (1000 - x) * set->x_step; // change 1000 for width
}

void draw_screen(t_args *args, t_set *set, t_data *img)
{
	int           i_y = 0;
	int           i_x = 0;
	double        real;
	double        irreal;
	unsigned char red;
	clock_t       start, end;    ///////////
	double        cpu_time_used; ////////
	start = clock();             ///////////
	while (i_y < args->high)
	{
		i_x = 0;
		while (i_x < args->width)
		{
			real = x_pixel(i_x, set->x_min, set->x_step);
			irreal = y_pixel(i_y, set->y_max, set->x_step);
			red = mandelbrotEscapeIterations(real, irreal, 150) & 0xFF;
			if (red < 5)
				my_mlx_pixel_put(img, i_x, i_y, argb(0, 224, 225, 221));
			else if (red < 20)
				my_mlx_pixel_put(img, i_x, i_y, argb(0, 119, 141, 169));
			else if (red < 50)
				my_mlx_pixel_put(img, i_x, i_y, argb(0, 65, 90, 119));
			else if (red < 100)
				my_mlx_pixel_put(img, i_x, i_y, argb(0, 27, 38, 59));
			else
				my_mlx_pixel_put(img, i_x, i_y, argb(0, 13, 27, 42));
			i_x++;
		}
		i_y++;
	}

	end = clock();                                             /////
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; /////////////
	printf("Time used: %f seconds\n", cpu_time_used);          /////////////
}

int mouse_hook(int keycode, int x, int y, t_all *all)
{
	if (keycode == MOUSE_WHEEL_DOWN)
	{
		zoom(0.9, &all->set, x, y);
		draw_screen(&all->args, &all->set, &all->img);
		mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img, 0, 0);
	}
	if (keycode == MOUSE_WHEEL_UP)
	{
		zoom(1.2, &all->set, x, y);
		draw_screen(&all->args, &all->set, &all->img);
		mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img, 0, 0);
	}
	return (0);
}

void test()
{
	printf("lll\n");
}
int main(void)
{
	t_all all;

	all.args.high = 1000;
	all.args.width = 1000;
	all.set.y_max = 2.0;
	all.set.y_min = -2.0;
	all.set.x_max = 2.0;
	all.set.x_min = -2.0;
	all.set.x_step = (all.set.x_max - all.set.x_min) / (all.args.width - 1.0);
	all.set.y_step = (all.set.y_max - all.set.y_min) / (all.args.high - 1.0);
	printf("%f\n", all.set.x_max);

	all.vars.mlx = mlx_init();
	all.vars.win = mlx_new_window(all.vars.mlx, all.args.high, all.args.width, "Hello world!");
	all.img.img = mlx_new_image(all.vars.mlx, all.args.high, all.args.width);
	all.img.addr = mlx_get_data_addr(all.img.img, &all.img.bits_per_pixel,
	                                 &all.img.line_length, &all.img.endian);
	// test
	draw_screen(&all.args, &all.set, &all.img);
	// fin test
	mlx_put_image_to_window(all.vars.mlx, all.vars.win, all.img.img, 0, 0);
	mlx_hook(all.vars.win, 2, 1L << 0, close, &all.vars); // close windows
	mlx_mouse_hook(all.vars.win, mouse_hook, &all);
	mlx_loop(all.vars.mlx);
}
