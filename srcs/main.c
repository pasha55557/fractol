/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:03:58 by rsticks           #+#    #+#             */
/*   Updated: 2019/10/05 16:17:46 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"


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

	fractol = (t_fractol*)malloc(sizeof(t_fractol));
	if (argc != 2)
	{
		ft_putendl("USAGE: ./fractol mandelbrot, julia");
		exit(1);
	}
	if (ft_strequ(argv[1], "mandelbrot") == 1)
	{
		fractol->id = 1;
		//fractol_mandelbrot(fractol);
	}
	else if (ft_strequ(argv[1], "julia") == 1)
	{
		fractol->id = 2;
		fractol->k = init_complex(-0.9, 0.3);
	}
	else
	{
		ft_putendl("USAGE: ./fractol mandelbrot, julia");
		exit(1);
	}
	init_mlx(fractol);
	//init fractol
	fractol->min = init_complex(-4.0, -2.0);
	fractol->max.re = 4.0;
	fractol->max.im = 2.0; //fractol->min.im + (fractol->max.re - fractol->min.re) * HEIGHT / WIDTH; //2.5 for 1080 p
	fractol->zoom = 35;

	ft_init_cl(fractol);
	mlx_hook(fractol->mlx.win, 2, 0, key_hook, fractol);
	mlx_hook(fractol->mlx.win, 6, 0, (int (*)())mouse_move, fractol);
	mlx_hook(fractol->mlx.win, 17, 0, (int (*)())exit, fractol);
	mlx_loop(fractol->mlx.mlx);
return(0);
}