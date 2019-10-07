/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 16:37:12 by rsticks           #+#    #+#             */
/*   Updated: 2019/10/07 20:26:05 by rsticks          ###   ########.fr       */
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
    if (x >= 0 && x <= WIDTH)
		fractol->x = x;
	else if (x < 0)
		fractol->x = 0;
	else
		fractol->x = WIDTH;
	if (y >= 0 && y <= HEIGHT)
		fractol->y = y;
	else if (y < 0)
		fractol->y = 0;
	else
		fractol->y = HEIGHT;
	if (fractol->space == 1)
	{
		fractol->k = init_complex(4 * ((double)x / WIDTH - 0.5), 4 * ((double)(HEIGHT - y) / HEIGHT - 0.5));
		start_kernel(fractol);
	}
	return(0);
}

void de_zoom(t_fractol *fractol)
{
	double	x_m;
	double	y_m;
	t_im	cent;

	x_m = WIDTH / (fractol->max.re - fractol->min.re);
	y_m = HEIGHT / (fractol->max.im - fractol->min.im);
	cent.re = (fractol->x / x_m) + fractol->min.re;	
	cent.im = -((fractol->y / y_m) - fractol->max.im);
	fractol->min.re = fractol->min.re - (cent.re - fractol->min.re) / fractol->zoom;
	fractol->max.re = fractol->max.re + (fractol->max.re - cent.re) / fractol->zoom;
	fractol->min.im = fractol->min.im - (cent.im - fractol->min.im) / fractol->zoom;
	fractol->max.im = fractol->max.im + (fractol->max.im - cent.im) / fractol->zoom;
}

void zoom(t_fractol *fractol)
{
	double	x_m;
	double	y_m;
	t_im	cent;

	x_m = WIDTH / (fractol->max.re - fractol->min.re);
	y_m = HEIGHT / (fractol->max.im - fractol->min.im);
	cent.re = (fractol->x / x_m) + fractol->min.re;	
	cent.im = -((fractol->y / y_m) - fractol->max.im);
	fractol->min.re = fractol->min.re + (cent.re - fractol->min.re) / fractol->zoom;
	fractol->max.re = fractol->max.re - (fractol->max.re - cent.re) / fractol->zoom;
	fractol->min.im = fractol->min.im + (cent.im - fractol->min.im) / fractol->zoom;
	fractol->max.im = fractol->max.im - (fractol->max.im - cent.im) / fractol->zoom;
}

int		key_hook(int key, t_fractol *fractol)
{
	double	offset;

	printf("%d\n", key);
	if (key == 83)
		if (fractol->r != 255)
			fractol->r += 2;
	if (key == 84)
		if (fractol->g != 255)
			fractol->g += 2;
	if (key == 85)
		if (fractol->b != 255)
			fractol->b += 2;
	if (key == 86)
		if (fractol->r != 0)
			fractol->r -= 2;
	if (key == 87)
		if (fractol->g != 0)
			fractol->g -= 2;
	if (key == 88)
		if (fractol->b != 0)
			fractol->b -= 2;
	if (key == 15) // R
		init_fractol(fractol);
	if (key == 116) // page up
	{
		if (fractol->id == 4)
			fractol->id = 1;
		else
			fractol->id++;
		init_fractol(fractol);
	}
	if (key == 67)
		fractol->max_iter++;
	if (key == 75)
		fractol->max_iter--;
	if (key == 27) // -
		de_zoom(fractol);
	if (key == 24) // +
		zoom(fractol);
	if (key == 124)
	{
		offset = ((fractol->max.re - fractol->min.re) / fractol->zoom) / 2;
		fractol->min.re = fractol->min.re - offset;
		fractol->max.re = fractol->max.re - offset;
	}
	
	if (key == 125)
	{
		offset = ((fractol->max.re - fractol->min.re) / fractol->zoom) / 2;
		fractol->min.im = fractol->min.im + offset;
		fractol->max.im = fractol->max.im + offset;
	}
	
	if (key == 126)
	{
		offset = ((fractol->max.re - fractol->min.re) / fractol->zoom) / 2;
		fractol->min.im = fractol->min.im - offset;
		fractol->max.im = fractol->max.im - offset;
	}

	if (key == 123)
	{
		offset = ((fractol->max.re - fractol->min.re) / fractol->zoom) / 2;
		fractol->min.re = fractol->min.re + offset;
		fractol->max.re = fractol->max.re + offset;
	}
	start_kernel(fractol);
	if (key == 49 && fractol->id == 2)
	{
		if (fractol->space == 0)
			fractol->space = 1;
		else
			fractol->space = 0;
	}
	if (key == 53)
		exit(0);
	return(0);
}