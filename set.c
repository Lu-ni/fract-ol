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
		// Check if the magnitude of the complex number exceeds 2 (escape radius)
		if ((zReal * zReal + zImag * zImag) > 4)
		{
			break;
		}
		iter++;
	}

	return iter;
}