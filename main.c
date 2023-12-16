#include "fractol.h"
#include "keys.h"
#include "mlx/mlx.h"
#include <stdio.h>

void test()
{
	printf("lll\n");
}
void init(t_all *all, int argc, char **argv)
{
	all->args.high = 500;
	all->args.width = 500;
	all->set.y_max = 2.0;
	all->set.y_min = -2.0;
	all->set.x_max = 2.0;
	all->set.x_min = -2.0;
	all->set.x_step = (all->set.x_max - all->set.x_min) / (all->args.width - 1.0);
	all->set.y_step = (all->set.y_max - all->set.y_min) / (all->args.high - 1.0);

	all->vars.mlx = mlx_init();
	all->vars.win = mlx_new_window(all->vars.mlx, all->args.high, all->args.width, "Hello world!");
	all->img.img = mlx_new_image(all->vars.mlx, all->args.high, all->args.width);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel,
	                                  &all->img.line_length, &all->img.endian);
}

int main(int argc, char **argv)
{
	t_all all;

	init(&all, argc, argv);
	// test
	draw_screen(&all);
	// fin test
	mlx_put_image_to_window(all.vars.mlx, all.vars.win, all.img.img, 0, 0);
	mlx_hook(all.vars.win, 2, 1L << 0, key_hook, &all);
	mlx_mouse_hook(all.vars.win, mouse_hook, &all);
	mlx_loop(all.vars.mlx);
}
