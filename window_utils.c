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
	// create_color_set(all);
	while (i_y < all->args.high)
	{
		i_x = 0;
		while (i_x < all->args.width)
		{
			int val = all->pixels[i_x][i_y];
			if (all->colors.acid)
				my_mlx_pixel_put(&all->img, i_x, i_y, argb(0, (val * val + all->colors.i) & 0xff, (val * val) & 0xFF, (255 - val) & 0xFF));
			else{
				if (val == 255)
					my_mlx_pixel_put(&all->img, i_x, i_y, argb(0, 0, 0, 40));
				else if (val <= 51)
					my_mlx_pixel_put(&all->img, i_x, i_y, argb(0, val * 5, 0, 40));
				else if (val <= 102)
					my_mlx_pixel_put(&all->img, i_x, i_y, argb(0, (val - 51) * 5, 0, 40));
				else if (val <= 153)
					my_mlx_pixel_put(&all->img, i_x, i_y, argb(0, (val - 102) * 5, 0, 40));
				else
				my_mlx_pixel_put(&all->img, i_x, i_y, argb(0, val, 0, 40));
			}
			i_x++;
		}
		i_y++;
	}
}
