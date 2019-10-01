/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:04:09 by rsticks           #+#    #+#             */
/*   Updated: 2019/10/01 17:30:47 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <pthread.h>
# include <OpenCL/opencl.h>
# include "../libft/libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# define WIDTH 1920
# define HEIGHT 1080

typedef struct			s_cl
{
	cl_context			context;
	cl_command_queue	queue;
	cl_platform_id		*plat_id;
	cl_device_id		*dev_id;
	cl_uint				num_platforms;
	cl_uint				num_device;
	cl_kernel			kernel;
	cl_program			prog;
	cl_mem				d_mem;
	cl_mem				img;
	cl_mem				i_mem;
}						t_cl;


typedef struct			s_im
{
	double				im;
	double				re;
}						t_im;

typedef struct			s_mlx
{
	void				*img;
	int					*data;
	void				*mlx;
	void				*win;
	int					bpp;
	int					line_size;
	int					endiane;
}						t_mlx;

typedef struct			s_fractol
{
	t_cl				cl;
	t_im				k;
	t_im				max;
	t_im				min;
	t_im				factor;
	t_mlx				mlx;
	int					x;
	int					y;
	int					id;
}						t_fractol;

void	start_kernel(t_fractol *fractol);
void	ft_init_cl(t_fractol *fractol);
t_im	init_complex(double re, double im);
void	fractol_mandelbrot(t_fractol *fractol);
void	fractol_julia(t_fractol *fractol, t_im k);

# endif