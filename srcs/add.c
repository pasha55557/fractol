/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:45:07 by rsticks           #+#    #+#             */
/*   Updated: 2019/10/08 20:17:15 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

t_im	init_complex(double re, double im)
{
	t_im comp;

	comp.im = im;
	comp.re = re;
	return (comp);
}

void	key_hook_color(t_fractol *fractol, int key)
{
	if (key == 83)
		if (fractol->r != 16)
			fractol->r++;
	if (key == 84)
		if (fractol->g != 16)
			fractol->g++;
	if (key == 85)
		if (fractol->b != 16)
			fractol->b++;
	if (key == 86)
		if (fractol->r != 0)
			fractol->r--;
	if (key == 87)
		if (fractol->g != 0)
			fractol->g--;
	if (key == 88)
		if (fractol->b != 0)
			fractol->b--;
	if (key == 15)
		init_fractol(fractol);
}

void	key_hook_control(t_fractol *fractol, int key)
{
	if (key == 116)
	{
		if (fractol->id == 5)
			fractol->id = 1;
		else
			fractol->id++;
		init_fractol(fractol);
	}
	if (key == 67)
		fractol->max_iter++;
	if (key == 75)
		fractol->max_iter--;
	if (key == 27)
		de_zoom(fractol);
	if (key == 24)
		zoom(fractol);
	if (key == 53)
		exit(0);
	if (key == 49 && (fractol->id == 2 || fractol->id == 5))
	{
		if (fractol->space == 0)
			fractol->space = 1;
		else
			fractol->space = 0;
	}
}

void	key_hook_move(t_fractol *fractol, int key, double offset)
{
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
}
