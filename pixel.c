#include "fractol.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

double x_pixel(int x, double x_min, double x_step)
{
	return (x_min + x * x_step);
}

double y_pixel(int y, double y_max, double y_step)
{
	return (y_max - y * y_step);
}
