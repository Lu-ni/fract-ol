#include "fractol.h"

int argb(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
	int val;

	val = 0;
	val += a;
	val <<= 8;
	val += b;
	val <<= 8;
	val += c;
	val <<= 8;
	val += d;
	return (val);
}
