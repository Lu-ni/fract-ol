#ifndef FRACTOL_H
#define FRACTOL_H

#define MAX_PIXELS 500
#define MAGIC_NUM 5
#define JULIA_SET 1
#define MANDELBROT_SET 2
#define TRICORN_SET 3
typedef struct s_vars
{
	void *mlx;
	void *win;
} t_vars;

typedef struct s_set
{
	double y_max;
	double y_min;
	double x_max;
	double x_min;
	double y_step;
	double x_step;
} t_set;

typedef struct s_data
{
	void *img;
	char *addr;
	int   bits_per_pixel;
	int   line_length;
	int   endian;
} t_data;

typedef struct s_arg
{
	int high;
	int width;
} t_args;
typedef struct s_colors
{
	int          split[15];
	unsigned int i;
	unsigned int ii;
	int          magic;
	int 		acid;
} t_colors;
typedef struct s_all
{
	t_args   args;
	t_set    set;
	t_data   img;
	t_vars   vars;
	int      pixels[MAX_PIXELS][MAX_PIXELS];
	t_colors colors;
	int set_choice;
} t_all;

// pixel.c
void   my_mlx_pixel_put(t_data *data, int x, int y, int color);
double x_pixel(int x, double x_min, double x_step);
double y_pixel(int y, double y_max, double y_step);
// set.c
void calculate_set(t_all *all);
// colors.c
int  argb(unsigned char a, unsigned char b, unsigned char c, unsigned char d);
void create_color_set(t_all *all);
int  full_psy(t_all *all);
// windows_utils.c
void zoom(float zoom, t_all *all, int x, int y);
void draw_screen(t_all *all);
void translation(float coef, t_all *all, int key);
// hook.c
int key_hook(int keycode, t_all *all);
int mouse_hook(int keycode, int x, int y, t_all *all);
// init
void init_all(t_all *all, int argc, char **argv);
#endif
