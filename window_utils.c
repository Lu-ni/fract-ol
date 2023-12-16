#include "fractol.h"
#include "keys.h"
#include "mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void zoom(float zoom, t_all *all, int x, int y)
{
	double real;
	double irreal;

	real = x_pixel(x, all->set.x_min, all->set.x_step);
	irreal = y_pixel(y, all->set.y_max, all->set.y_step);
	all->set.x_step = all->set.x_step * zoom;
	all->set.y_step = all->set.y_step * zoom;
	all->set.y_max = irreal + y * all->set.y_step;
	all->set.y_min = irreal - (all->args.high - y) * all->set.y_step;
	all->set.x_min = real - x * all->set.x_step;
	all->set.x_max = real + (all->args.width - x) * all->set.x_step;
}

void translation(float coef, t_all *all, int key)
{
	float delta_y;
	float delta_x;

	delta_y = all->set.y_max - all->set.y_min;
	delta_x = all->set.x_max - all->set.x_min;
	if (key == UP)
	{
		all->set.y_max += delta_y * coef;
		all->set.y_min += delta_y * coef;
	}
	if (key == DOWN)
	{
		all->set.y_max -= delta_y * coef;
		all->set.y_min -= delta_y * coef;
	}
	if (key == RIGTH)
	{
		all->set.x_max += delta_x * coef;
		all->set.x_min += delta_x * coef;
	}
	if (key == LEFT)
	{
		all->set.x_max -= delta_x * coef;
		all->set.x_min -= delta_x * coef;
	}
}

void draw_screen(t_all *all)
{
	int           i_y = 0;
	int           i_x = 0;
	double        real;
	double        irreal;
	unsigned char red;
	clock_t       start, end;    ///////////
	double        cpu_time_used; ////////
	start = clock();             ///////////
	while (i_y < all->args.high)
	{
		i_x = 0;
		while (i_x < all->args.width)
		{
			real = x_pixel(i_x, all->set.x_min, all->set.x_step);
			irreal = y_pixel(i_y, all->set.y_max, all->set.x_step);
			red = mandelbrotEscapeIterations(real, irreal, 150) & 0xFF;
			// red = julia(i_x, i_y, -0.4, 0.6);
			if (red < 5)
				my_mlx_pixel_put(&all->img, i_x, i_y, argb(0, 224, 225, 221));
			else if (red < 20)
				my_mlx_pixel_put(&all->img, i_x, i_y, argb(0, 119, 141, 169));
			else if (red < 50)
				my_mlx_pixel_put(&all->img, i_x, i_y, argb(0, 65, 90, 119));
			else if (red < 100)
				my_mlx_pixel_put(&all->img, i_x, i_y, argb(0, 27, 38, 59));
			else
				my_mlx_pixel_put(&all->img, i_x, i_y, argb(0, 13, 27, 42));
			i_x++;
		}
		i_y++;
	}

	end = clock();                                             /////
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; /////////////
	printf("Time used: %f seconds\n", cpu_time_used);          /////////////
}
