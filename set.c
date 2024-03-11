#include "fractol.h"
#include <stdio.h>

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
		// Check if the magnitude of the complex number exceeds 2 (escape radius)
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
			//all->pixels[i_x][i_y] = mandelbrotEscapeIterations(real, irreal, 255) & 0xFF;
			all->pixels[i_x][i_y] = julia(real, irreal, -0.4, 0.6);
			i_x++;
		}
		i_y++;
	}
	i_y = 0;
}
