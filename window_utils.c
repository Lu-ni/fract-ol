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
	int i_y = 0;
	int i_x = 0;

	i_y = 0;
	calculate_set(all);
	create_color_set(all);
	while (i_y < all->args.high)
	{
		i_x = 0;
		while (i_x < all->args.width)
		{
			// my_mlx_pixel_put(&all->img, i_x, i_y, argb(0, 255, 200, all->pixels[i_x][i_y]));
			if (all->pixels[i_x][i_y] < all->colors.split[0])
				my_mlx_pixel_put(&all->img, i_x, i_y, argb(0, 40, 50, 20));
			else if (all->pixels[i_x][i_y] < all->colors.split[1])
				my_mlx_pixel_put(&all->img, i_x, i_y, argb(0, 40, 50, 40));
			else if (all->pixels[i_x][i_y] < all->colors.split[2])
				my_mlx_pixel_put(&all->img, i_x, i_y, argb(0, 40, 50, 60));
			else if (all->pixels[i_x][i_y] < all->colors.split[3])
				my_mlx_pixel_put(&all->img, i_x, i_y, argb(0, 40, 100, 80));
			else if (all->pixels[i_x][i_y] < all->colors.split[4])
				my_mlx_pixel_put(&all->img, i_x, i_y, argb(0, 40, 100, 100));
			else if (all->pixels[i_x][i_y] < all->colors.split[5])
				my_mlx_pixel_put(&all->img, i_x, i_y, argb(0, 40, 100, 120));
			else if (all->pixels[i_x][i_y] < all->colors.split[6])
				my_mlx_pixel_put(&all->img, i_x, i_y, argb(0, 40, 150, 140));
			else if (all->pixels[i_x][i_y] < all->colors.split[7])
				my_mlx_pixel_put(&all->img, i_x, i_y, argb(0, 40, 150, 160));
			else if (all->pixels[i_x][i_y] < all->colors.split[8])
				my_mlx_pixel_put(&all->img, i_x, i_y, argb(0, 40, 150, 180));
			else
				my_mlx_pixel_put(&all->img, i_x, i_y, argb(0, 40, 200, 200));
			i_x++;
		}
		i_y++;
	}
}
