#ifndef FRACTOL_H
#define FRACTOL_H

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct	s_set {
	double	y_max;
	double	y_min;
	double	x_max;
	double	x_min;
	double  y_step;
	double  x_step;
}				t_set;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_arg{
	int high;
	int width;
} t_args;
typedef struct s_zoom{
	t_args *args;
	t_set *set;
	t_data *img;
	t_vars *vars;
} t_zoom;
#endif
