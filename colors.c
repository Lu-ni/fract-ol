#include "fractol.h"
#include <stdio.h>

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
void create_color_set(t_all *all)
{
	int tab[256];
	int i_x;
	int i_y;
	int total = all->args.high * all->args.width;

	int i = 0;
	int sum = 0;
	while (i < 256)
		tab[i++] = 0;
	i_y = 0;
	while (i_y < all->args.high)
	{
		i_x = 0;
		while (i_x < all->args.width)
			tab[all->pixels[i_x++][i_y]] += 1;
		i_y++;
	}
	i = 0;
	int count = 0;
	int div = 10;
	printf("///////\n");
	while (i < 256)
	{
		count += tab[i];
		if (count > total / div)
		{
			all->colors.split[10 - div] = i;
			printf("set limit:%i\n", i);
			total -= count;
			count = 0;
			div--;
		}
		i++;
	}
}
