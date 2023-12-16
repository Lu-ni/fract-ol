#ifndef FRACTOL_H
#define FRACTOL_H

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
typedef struct s_all
{
	t_args args;
	t_set  set;
	t_data img;
	t_vars vars;
} t_all;
// pixel.c
void   my_mlx_pixel_put(t_data *data, int x, int y, int color);
double x_pixel(int x, double x_min, double x_step);
double y_pixel(int y, double y_max, double y_step);
// set.c
int mandelbrotEscapeIterations(double real, double imag, int maxIter);
int julia(float x, float y, float cX, float cY);
// colors.c
int argb(unsigned char a, unsigned char b, unsigned char c, unsigned char d);
// windows_utils.c
void zoom(float zoom, t_all *all, int x, int y);
void draw_screen(t_all *all);
void translation(float coef, t_all *all, int key);
// hook.c
int key_hook(int keycode, t_all *all);
int mouse_hook(int keycode, int x, int y, t_all *all);
#endif
