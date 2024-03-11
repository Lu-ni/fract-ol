#include "fractol.h"

int mandelbrotEscapeIterations(double real, double imag, int maxIter)
{
	double       zReal = 0.0;
	double       zImag = 0.0;
	unsigned int iter = 0;
	double       zRealNew;
	double       zImagNew;

	while (iter < maxIter)
	{
		zRealNew = zReal * zReal - zImag * zImag + real;
		zImagNew = 2 * zReal * zImag + imag;
		zReal = zRealNew;
		zImag = zImagNew;
		if ((zReal * zReal + zImag * zImag) > 4)
		{
			break;
		}
		iter++;
	}
	return iter;
}

int julia(float x, float y, float cX, float cY)
{
	int   iter = 0;
	float zx = x;
	float zy = y;

	while (zx * zx + zy * zy <= 4.0 && iter < 255)
	{
		float xt = zx * zx - zy * zy + cX;
		zy = 2.0 * zx * zy + cY;
		zx = xt;
		iter++;
	}
	return iter;
}
int tricorn(double real, double irreal, int max_iterations)
{
    double z_real = real;
    double z_irreal = irreal;
    int iter = 0;

    while (z_real * z_real + z_irreal * z_irreal <= 4.0 && iter < max_iterations)
    {
        double temp = z_real * z_real - z_irreal * z_irreal + real;
        z_irreal = -2.0 * z_real * z_irreal + irreal;
        z_real = temp;
        iter++;
    }

    return iter;
}

void calculate_set(t_all *all)
{
	int           i_y = 0;
	int           i_x = 0;
	double        real;
	double        irreal;
	unsigned char red;
	while (i_y < all->args.high)
	{
		i_x = 0;
		while (i_x < all->args.width)
		{
			real = x_pixel(i_x, all->set.x_min, all->set.x_step);
			irreal = y_pixel(i_y, all->set.y_max, all->set.x_step);
			if(all->set_choice == MANDELBROT_SET)
				all->pixels[i_x][i_y] = mandelbrotEscapeIterations(real, irreal, 255) & 0xFF;
			if(all->set_choice == JULIA_SET)
				all->pixels[i_x][i_y] = julia(real, irreal, all->set.cX, all->set.cY);
			if(all->set_choice == TRICORN_SET)
				all->pixels[i_x][i_y] = tricorn(real, irreal, 255);
			i_x++;
		}
		i_y++;
	}
	i_y = 0;
}
