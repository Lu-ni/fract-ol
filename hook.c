#include "fractol.h"
#include "keys.h"
#include "mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int mouse_hook(int keycode, int x, int y, t_all *all)
{
	if (keycode == MOUSE_WHEEL_DOWN)
	{
		zoom(0.9, all, x, y);
		draw_screen(all);
		mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img, 0, 0);
	}
	if (keycode == MOUSE_WHEEL_UP)
	{
		zoom(1.2, all, x, y);
		draw_screen(all);
		mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img, 0, 0);
	}
	return (0);
}
int key_hook(int keycode, t_all *all)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(all->vars.mlx, all->vars.win);
		exit(EXIT_SUCCESS);
	}
	else if (123 <= keycode && keycode <= 126)
	{
		translation(0.05, all, keycode);
		draw_screen(all);
		mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img, 0, 0);
	}
	else
	{
		printf("%i\n", keycode);
	}
	return (0);
}
