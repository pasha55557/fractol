/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:03:58 by rsticks           #+#    #+#             */
/*   Updated: 2019/10/08 18:50:04 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

static void usage(char *argv, int argc, t_fractol *fractol)
{
	if (ft_strequ(argv, "mandelbrot") == 1)
		fractol->id = 1;
	else if (ft_strequ(argv, "julia") == 1)
		fractol->id = 2;
	else if (ft_strequ(argv, "Burningship") == 1)
		fractol->id = 3;
	else if (ft_strequ(argv, "Mandelbar") == 1)
		fractol->id = 4;
	else if (ft_strequ(argv, "tanhjulia") == 1)
		fractol->id = 5;
	if (argc != 2 || !(fractol->id >= 1 && fractol->id <= 5))
	{
		ft_putendl("USAGE: ./fractol mandelbrot, julia, Burningship, Mandelbar, tanhjulia");
		exit(1);
	}
}
void	string_print(t_fractol *fractol)
{
	mlx_string_put(fractol->mlx.mlx, fractol->mlx.win, 30, 30, 0xFFFFFF, "press +, mouse wheel to zoom");
	mlx_string_put(fractol->mlx.mlx, fractol->mlx.win, 30, 50, 0xFFFFFF, "press -, mouse wheel to dezoom");
	mlx_string_put(fractol->mlx.mlx, fractol->mlx.win, 30, 70, 0xFFFFFF, "press R to reboot fractal");
	mlx_string_put(fractol->mlx.mlx, fractol->mlx.win, 30, 90, 0xFFFFFF, "press arrows to move fractal");
	mlx_string_put(fractol->mlx.mlx, fractol->mlx.win, 30, 110, 0xFFFFFF, "press PAGE UP to change fractal");
	mlx_string_put(fractol->mlx.mlx, fractol->mlx.win, 30, 130, 0xFFFFFF, "press NUM 1,2,3,4,5,6 to change color");
	if (fractol->id == 2 || fractol->id == 5)
		mlx_string_put(fractol->mlx.mlx, fractol->mlx.win, 30, 1000, 0xFFFFFF, "press SPACE to magic");
}

void	init_fractol(t_fractol *fractol)
{
	fractol->min = init_complex(-4.0, -2.0);
	fractol->max.re = 4.0;
	fractol->max.im = fractol->min.im + (fractol->max.re - fractol->min.re) * HEIGHT / WIDTH;
	fractol->zoom = 25;
	fractol->k = init_complex(-0.9, 0.3);
	fractol->max_iter = 50;
	fractol->r = 16;
	fractol->g = 8;
	fractol->b = 0;
}

static void		init_mlx(t_fractol *fractol)
{
	fractol->mlx.mlx = mlx_init();
	fractol->mlx.win = mlx_new_window(fractol->mlx.mlx, WIDTH, HEIGHT, "Fractol");
	fractol->mlx.img = mlx_new_image(fractol->mlx.mlx, WIDTH, HEIGHT);
	fractol->mlx.data = (int*)mlx_get_data_addr(fractol->mlx.img, &fractol->mlx.bpp, &fractol->mlx.line_size, &fractol->mlx.endiane);
	fractol->mlx.bpp /= 8;
}

int				main(int argc, char **argv)
{
	t_fractol 	*fractol;

	fractol = (t_fractol*)malloc(sizeof(t_fractol));
	usage(argv[1], argc, fractol);
	init_mlx(fractol);
	init_fractol(fractol);	
	init_cl(fractol);
	mlx_hook(fractol->mlx.win, 2, 0, key_hook, fractol);
	mlx_hook(fractol->mlx.win, 6, 0, (int (*)())mouse_move, fractol);
	mlx_hook(fractol->mlx.win, 4, 0, mouse_event, fractol);
	mlx_hook(fractol->mlx.win, 17, 0, (int (*)())exit, fractol);
	string_print(fractol);
	mlx_loop(fractol->mlx.mlx);
return(0);
}