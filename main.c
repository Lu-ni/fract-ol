#include "fractol.h"
#include "keys.h"
#include "mlx/mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int psy(t_all *all)
{
	if (full_psy(all))
	{
		draw_screen(all);
		mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img, 0, 0);
	}
	return (0);
}
void print_help(void)
{
	write(1, "test\n",5);
	exit(EXIT_SUCCESS);
}
int parser(t_all *all, int argc, char **argv)
{
	if(argc < 2)
		print_help();
	else if (argv[1][0] == 'j' && argv[1][1] == '\0' && argc == 4) //protect against no args
	{
		all->set_choice = JULIA_SET;
		all->set.cX = atof(argv[2]);
		all->set.cY = atof(argv[3]);
	}
	else if (argv[1][0] == 'm' && argv[1][1] == '\0')
		all->set_choice = MANDELBROT_SET;
	else if (argv[1][0] == 't' && argv[1][1] == '\0')
		all->set_choice = TRICORN_SET;
	else
		print_help();
	return (0);
}
void init(t_all *all, int argc, char **argv)
{
	parser(all, argc, argv);
	init_all(all, argc, argv);
}

int main(int argc, char **argv)
{
	t_all all;

	init(&all, argc, argv);
	// test
	calculate_set(&all);
	draw_screen(&all);
	// fin test
	mlx_put_image_to_window(all.vars.mlx, all.vars.win, all.img.img, 0, 0);
	mlx_hook(all.vars.win, 2, 1L << 0, key_hook, &all);
	mlx_mouse_hook(all.vars.win, mouse_hook, &all);
	mlx_loop_hook(all.vars.mlx, psy, &all);
	mlx_loop(all.vars.mlx);
}
