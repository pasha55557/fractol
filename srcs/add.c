/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:45:07 by rsticks           #+#    #+#             */
/*   Updated: 2019/10/01 15:27:16 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

static int		set_color(double t)
{
	int r;
	int g;
	int b;

	r = (int)(9 * (1 - t) * pow(t, 3) * 255);
	g = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
	b = (int)(8.5 * pow((1 - t), 3) * t * 255);
	return ((b << 16) | (g << 8) | r);
}

t_im	init_complex(double re, double im)
{
	t_im comp;

	comp.im = im;
	comp.re = re;
	return(comp);
}

void	fractol_mandelbrot(t_fractol *fractol)
{
	int		max_iter;
	int		iter;
	int		x;
	int		y;
	double	t;
	int		rgb;
	t_im	z;
	t_im	c;

	fractol->factor = init_complex((fractol->max.re - fractol->min.re) / (WIDTH - 1), (fractol->max.im - fractol->min.im) / (HEIGHT - 1));
	max_iter = 50;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			c.im = fractol->max.im - y * fractol->factor.im;
			c.re = fractol->min.re + x * fractol->factor.re;
			z = init_complex(c.re, c.im);
			iter = 0;
			while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 && iter < max_iter)
			{
				z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0) + c.re, 2.0 * z.re * z.im + c.im);
				// формула
				iter++;
			}
			t = (double)iter / (double)max_iter;
			rgb = set_color(t);
			fractol->mlx.data[x + (y * WIDTH)] = rgb;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractol->mlx.mlx, fractol->mlx.win, fractol->mlx.img, 0, 0);
}

void	fractol_julia(t_fractol *fractol, t_im k)
{
	t_im	c;
	t_im	z;
	int		max_iter;
	int		iter;
	int		rgb;
	int		x;
	int		y;
	double	t;

	fractol->factor = init_complex((fractol->max.re - fractol->min.re) / (WIDTH - 1), (fractol->max.im - fractol->min.im) / (HEIGHT - 1));
	max_iter = 50;
	y = 0;
	while (y < HEIGHT)
	{
		c.im = fractol->max.im - y * fractol->factor.im;
    	x = 0;
		while (x < WIDTH)
		{
			c.re = fractol->min.re + x * fractol->factor.re;
			z = init_complex(c.re, c.im);
			iter = 0;
			while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 && iter < max_iter)
			{
				 z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0) + k.re, 2.0 * z.re * z.im + k.im);
    		iter++;
			}
			if (iter == max_iter)
				rgb = 0;
			else
			{
				t = ((double)iter / (double)max_iter);
				rgb = set_color(t);
			}
			fractol->mlx.data[x + (y * WIDTH)] = rgb;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractol->mlx.mlx, fractol->mlx.win, fractol->mlx.img, 0, 0);
}