/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 16:37:12 by rsticks           #+#    #+#             */
/*   Updated: 2019/10/05 18:14:06 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

double	ft_abc(double a)
{
	if (a < 0)
	{
		a = a * (-1);
		return (a);
	}
	return (0);
}

int 	mouse_move(int x, int y, t_fractol *fractol)
{
    if (x >= 0 && x <= HEIGHT)
		fractol->x = x;
	else if (x < 0)
		fractol->x = 0;
	else
		fractol->x = HEIGHT;
	if (y >= 0 && y <= WIDTH)
		fractol->y = y;
	else if (y < 0)
		fractol->y = 0;
	else
		fractol->y = WIDTH;
	if (fractol->space == 1)
	{
		fractol->k = init_complex(4 * ((double)x / WIDTH - 0.5), 4 * ((double)(HEIGHT - y) / HEIGHT - 0.5));
		start_kernel(fractol);
	}
	return(0);
}

void zoom(t_fractol *fractol)
{
	double	x_m;
	double	y_m;
	t_im	cent;

	x_m = WIDTH / (fractol->max.re - fractol->min.re);
	y_m = HEIGHT / (fractol->max.im - fractol->min.im);
	if (ft_abc(fractol->min.re) * x_m > fractol->x)
		cent.re = (fractol->x / x_m) + fractol->min.re;
	if (ft_abc(fractol->min.im) * y_m < fractol->y)
		cent.im = (fractol->y / y_m) + fractol->min.im;
	else
		cent.im = -(fractol->y / y_m - fractol->max.im);

	fractol->min.re = fractol->min.re + (cent.re - fractol->min.re) / fractol->zoom;
	fractol->max.re = fractol->max.re - (fractol->max.re - cent.re) / fractol->zoom;
	fractol->min.im = fractol->min.im + (cent.im - fractol->min.im) / fractol->zoom;
	fractol->max.im = fractol->max.im - (fractol->max.im - cent.im) / fractol->zoom;
}

int		key_hook(int key, t_fractol *fractol)
{
	if (key == 27)
	{
		fractol->min = init_complex(fractol->min.re * 1.2, fractol->min.im * 1.2);
		fractol->max = init_complex(fractol->max.re * 1.2, fractol->max.im * 1.2);
		start_kernel(fractol);
	}
	if (key == 24)
	{
		zoom(fractol);
		start_kernel(fractol);
	}
	if (key == 124)
	{
		fractol->min.re = fractol->min.re - (fractol->max.re / 20);
		fractol->max.re = fractol->max.re - (fractol->max.re / 20);
		start_kernel(fractol);
	}
	
	if (key == 125)
	{
		fractol->min.im = fractol->min.im + (fractol->max.im / 20);
		fractol->max.im = fractol->max.im + (fractol->max.im / 20);
		start_kernel(fractol);
	}
	
	if (key == 126)
	{
		fractol->min.im = fractol->min.im - (fractol->max.im / 20);
		fractol->max.im = fractol->max.im - (fractol->max.im / 20);
		start_kernel(fractol);
	}

	if (key == 123)
	{
		fractol->min.re = fractol->min.re + (fractol->max.re / 20);
		fractol->max.re = fractol->max.re + (fractol->max.re / 20);
		start_kernel(fractol);
	}
	
	if (key == 49 && fractol->id == 2)
	{
		printf("%s\n", "key pressed");
		if (fractol->space == 0)
			fractol->space = 1;
		else
			fractol->space = 0;
	}
	if (key == 53)
		exit(0);
	return(0);
}