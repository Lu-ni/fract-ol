#include "fractol.h"
#include "keys.h"
#include "mlx/mlx.h"
#include <stdlib.h>



int **twod_image(t_all *all) {
    int i;
    int **image;
	int j;

    image = (int **)malloc(all->args.high * sizeof(int *));
    if (image == NULL) {
        return NULL;
    }

    i = 0;
    while (i < all->args.high) {
        image[i] = (int *)malloc(all->args.width * sizeof(int));
        if (image[i] == NULL) {
            j = 0;
            while (j < i) {
                free(image[j]);
                j++;
            }
            free(image);
            return NULL;
        }
        i++;
    }

    return image;
}

void init_all(t_all *all, int argc, char **argv)
{
	all->colors.magic = MAGIC_NUM;
	all->colors.acid = 0;
	all->args.high = 1000;
	all->args.width = 1000;
	all->pixels = twod_image(all);
	all->set.y_max = 2.0;
	all->set.y_min = -2.0;
	all->set.x_max = 2.0;
	all->set.x_min = -2.0;
	all->set.x_step = (all->set.x_max - all->set.x_min) / (all->args.width - 1.0);
	all->set.y_step = (all->set.y_max - all->set.y_min) / (all->args.high - 1.0);

	all->vars.mlx = mlx_init();
	all->vars.win = mlx_new_window(all->vars.mlx, all->args.high, all->args.width, "fract-ol");
	all->img.img = mlx_new_image(all->vars.mlx, all->args.high, all->args.width);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel,
	                                  &all->img.line_length, &all->img.endian);
}
