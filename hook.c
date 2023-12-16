#include "fractol.h"
#include "keys.h"
#include "mlx/mlx.h"

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
