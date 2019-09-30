/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:03:58 by rsticks           #+#    #+#             */
/*   Updated: 2019/09/30 14:16:38 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int 	mouse_move(int x, int y, t_fractol *fractol)
{
	t_im	k;

	if (fractol->x == 1)
	{
		k = init_complex(4 * ((double)x / WIDTH - 0.5), 4 * ((double)(HEIGHT - y) / HEIGHT - 0.5));
		fractol_julia(fractol, k);
	}
	return(0);
}

int		key_hook(int key, t_fractol *fractol)
{
	if (key == 27)
	{
		fractol->min = init_complex(fractol->min.re * 1.2, fractol->min.im * 1.2);
		fractol->max = init_complex(fractol->max.re * 1.2, fractol->max.im * 1.2);
		//fractol->max.re = fractol->max.re + 0.1;
		if (fractol->id == 1)
			fractol_mandelbrot(fractol);
		else if (fractol->id == 2)
			fractol_julia(fractol, init_complex(-0.9, 0.3));
	}
	if (key == 24)
	{
		//printf("%f\n", fractol->min.re);
		fractol->min = init_complex(fractol->min.re / 1.2, fractol->min.im / 1.2);
		fractol->max = init_complex(fractol->max.re / 1.2, fractol->max.im / 1.2);
		//fractol->max.re = fractol->max.re - 0.1;
		if (fractol->id == 1)
			fractol_mandelbrot(fractol);
		else if (fractol->id == 2)
			fractol_julia(fractol, init_complex(-0.9, 0.3));
	}
	if (key == 124)
	{
		fractol->min.re = fractol->min.re - (fractol->max.re / 20);
		fractol->max.re = fractol->max.re - (fractol->max.re / 20);
		if (fractol->id == 1)
			fractol_mandelbrot(fractol);
		else if (fractol->id == 2)
			fractol_julia(fractol, init_complex(-0.9, 0.3));
	}
	
	if (key == 125)
	{
		fractol->min.im = fractol->min.im + (fractol->max.im / 20);
		fractol->max.im = fractol->max.im + (fractol->max.im / 20);
		if (fractol->id == 1)
			fractol_mandelbrot(fractol);
		else if (fractol->id == 2)
			fractol_julia(fractol, init_complex(-0.9, 0.3));
	}
	
	if (key == 126)
	{
		fractol->min.im = fractol->min.im - (fractol->max.im / 20);
		fractol->max.im = fractol->max.im - (fractol->max.im / 20);
		if (fractol->id == 1)
			fractol_mandelbrot(fractol);
		else if (fractol->id == 2)
			fractol_julia(fractol, init_complex(-0.9, 0.3));
	}

	if (key == 123)
	{
		fractol->min.re = fractol->min.re + (fractol->max.re / 20);
		fractol->max.re = fractol->max.re + (fractol->max.re / 20);
		if (fractol->id == 1)
			fractol_mandelbrot(fractol);
		else if (fractol->id == 2)
			fractol_julia(fractol, init_complex(-0.9, 0.3));
	}
	
	if (key == 49 && fractol->id == 2)
	{
		printf("%s\n", "key pressed");
		if (fractol->x == 0)
			fractol->x = 1;
		else
			fractol->x = 0;
	}
	if (key == 53)
		exit(0);
	return(0);
}

static void		init_mlx(t_fractol *fractol)
{
	fractol->mlx.mlx = mlx_init();
	fractol->mlx.win = mlx_new_window(fractol->mlx.mlx, WIDTH, HEIGHT, "Fractol");
	fractol->mlx.img = mlx_new_image(fractol->mlx.mlx, WIDTH, HEIGHT);
	fractol->mlx.data = (int*)mlx_get_data_addr(fractol->mlx.img, &fractol->mlx.bpp, &fractol->mlx.line_size, &fractol->mlx.endiane);
	fractol->mlx.bpp /= 8;
}

int		main(int argc, char **argv)
{
	t_fractol 		*fractol;


		if (argc != 2)
	{
		ft_putendl("USAGE: ./fractol mandelbrot, julia");
		exit(1);
	}
	fractol = (t_fractol*)malloc(sizeof(t_fractol));
	init_mlx(fractol);
	//init fractol
	fractol->min = init_complex(-4.0, -2.0);
	fractol->max.re = 4.0;
	fractol->max.im = fractol->min.im + (fractol->max.re - fractol->min.re) * HEIGHT / WIDTH;
	if (ft_strequ(argv[1], "mandelbrot") == 1)
	{
		fractol->id = 1;
		//fractol_mandelbrot(fractol);
	}
	if (ft_strequ(argv[1], "julia") == 1)
	{
		fractol->id = 2;
		//fractol_julia(fractol, init_complex(-0.9, 0.3));
	}
	ft_init_cl(fractol);
	//mlx_hook(fractol->mlx.win, 2, 0, key_hook, fractol);
	//mlx_hook(fractol->mlx.win, 6, 0, (int (*)())mouse_move, fractol);
	mlx_hook(fractol->mlx.win, 17, 0, (int (*)())exit, fractol);
	mlx_loop(fractol->mlx.mlx);
return(0);
}