/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 16:37:12 by rsticks           #+#    #+#             */
/*   Updated: 2019/10/08 20:47:01 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int			mouse_event(int key, int x, int y, t_fractol *fractol)
{
	if (x < 0 || y < 0)
		return (0);
	if (key == 5)
		de_zoom(fractol);
	if (key == 4)
		zoom(fractol);
	start_kernel(fractol);
	string_print(fractol);
	return (0);
}

int			mouse_move(int x, int y, t_fractol *fractol)
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
		fractol->k = init_complex(4 * ((double)x / WIDTH - 0.5),
		4 * ((double)(HEIGHT - y) / HEIGHT - 0.5));
		start_kernel(fractol);
		string_print(fractol);
	}
	return (0);
}

void		de_zoom(t_fractol *fractol)
{
	double	x_m;
	double	y_m;
	t_im	cent;

	x_m = WIDTH / (fractol->max.re - fractol->min.re);
	y_m = HEIGHT / (fractol->max.im - fractol->min.im);
	cent.re = (fractol->x / x_m) + fractol->min.re;
	cent.im = -((fractol->y / y_m) - fractol->max.im);
	fractol->min.re = fractol->min.re -
	(cent.re - fractol->min.re) / fractol->zoom;
	fractol->max.re = fractol->max.re +
	(fractol->max.re - cent.re) / fractol->zoom;
	fractol->min.im = fractol->min.im -
	(cent.im - fractol->min.im) / fractol->zoom;
	fractol->max.im = fractol->max.im +
	(fractol->max.im - cent.im) / fractol->zoom;
}

void		zoom(t_fractol *fractol)
{
	double	x_m;
	double	y_m;
	t_im	cent;

	x_m = WIDTH / (fractol->max.re - fractol->min.re);
	y_m = HEIGHT / (fractol->max.im - fractol->min.im);
	cent.re = (fractol->x / x_m) + fractol->min.re;
	cent.im = -((fractol->y / y_m) - fractol->max.im);
	fractol->min.re = fractol->min.re +
	(cent.re - fractol->min.re) / fractol->zoom;
	fractol->max.re = fractol->max.re -
	(fractol->max.re - cent.re) / fractol->zoom;
	fractol->min.im = fractol->min.im +
	(cent.im - fractol->min.im) / fractol->zoom;
	fractol->max.im = fractol->max.im -
	(fractol->max.im - cent.im) / fractol->zoom;
}

int			key_hook(int key, t_fractol *fractol)
{
	double	offset;

	offset = 0.0;
	key_hook_color(fractol, key);
	key_hook_control(fractol, key);
	key_hook_move(fractol, key, offset);
	start_kernel(fractol);
	string_print(fractol);
	return (0);
}
