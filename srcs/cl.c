/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:01:51 by rsticks           #+#    #+#             */
/*   Updated: 2019/10/08 20:40:07 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

static void		mem_to_kernel(double *dm, int *im, t_fractol *fractol)
{
	dm[0] = fractol->min.im;
	dm[1] = fractol->min.re;
	dm[2] = fractol->max.im;
	dm[3] = fractol->max.re;
	dm[4] = fractol->k.re;
	dm[5] = fractol->k.im;
	im[0] = fractol->b;
	im[1] = fractol->g;
	im[2] = fractol->r;
	im[3] = fractol->max_iter;
	im[4] = fractol->id;
	im[5] = WIDTH;
	im[6] = HEIGHT;
}

static void		init_cl_two(t_fractol *f, int err)
{
	int			i;
	int			fd;
	char		*k_s;
	size_t		k_l;

	fd = open("kernel.cl", O_RDONLY);
	k_s = (char*)malloc(sizeof(char) * 5970);
	i = read(fd, k_s, 5970);
	k_s[i] = '\0';
	k_l = ft_strlen(k_s);
	f->cl.prog = clCreateProgramWithSource(f->cl.context, 1,
	(const char**)&k_s, &k_l, &err);
	err = clBuildProgram(f->cl.prog, 1, f->cl.dev_id, NULL, NULL, NULL);
	f->cl.kernel = clCreateKernel(f->cl.prog, "start", &err);
	f->cl.d_mem = clCreateBuffer(f->cl.context,
	CL_MEM_READ_WRITE, sizeof(double) * 6, NULL, &err);
	f->cl.img = clCreateBuffer(f->cl.context, CL_MEM_READ_WRITE,
	sizeof(int) * WIDTH * HEIGHT, NULL, &err);
	f->cl.i_mem = clCreateBuffer(f->cl.context, CL_MEM_READ_WRITE,
	sizeof(int) * 7, NULL, &err);
	err = clSetKernelArg(f->cl.kernel, 0, sizeof(cl_mem), &f->cl.i_mem);
	err = clSetKernelArg(f->cl.kernel, 1, sizeof(cl_mem), &f->cl.d_mem);
	err = clSetKernelArg(f->cl.kernel, 2, sizeof(cl_mem), &f->cl.img);
	start_kernel(f);
	ft_strdel(&k_s);
}

void			init_cl(t_fractol *f)
{
	int			error;

	error = clGetPlatformIDs(0, NULL, &f->cl.num_platforms);
	f->cl.plat_id = (cl_platform_id *)malloc(sizeof(cl_platform_id)
	* f->cl.num_platforms);
	error = clGetPlatformIDs(f->cl.num_platforms, f->cl.plat_id, NULL);
	error = clGetDeviceIDs(f->cl.plat_id[0], CL_DEVICE_TYPE_GPU, 0,
	NULL, &f->cl.num_device);
	f->cl.dev_id = (cl_device_id *)malloc(sizeof(cl_device_id)
	* f->cl.num_device);
	error = clGetDeviceIDs(f->cl.plat_id[0], CL_DEVICE_TYPE_GPU,
	f->cl.num_device, f->cl.dev_id, NULL);
	f->cl.context = clCreateContext(NULL, 1, f->cl.dev_id, NULL, NULL, &error);
	f->cl.queue = clCreateCommandQueue(f->cl.context,
	f->cl.dev_id[0], 0, &error);
	init_cl_two(f, error);
}

void			start_kernel(t_fractol *f)
{
	int			err;
	double		dm[6];
	int			im[7];
	size_t		gws;

	mem_to_kernel(dm, im, f);
	gws = WIDTH * HEIGHT;
	err = clEnqueueWriteBuffer(f->cl.queue, f->cl.i_mem, CL_TRUE,
	0, sizeof(int) * 7, im, 0, NULL, NULL);
	err = clEnqueueWriteBuffer(f->cl.queue, f->cl.d_mem, CL_TRUE,
	0, sizeof(double) * 6, dm, 0, NULL, NULL);
	err = clEnqueueNDRangeKernel(f->cl.queue, f->cl.kernel, 1, NULL,
	&gws, NULL, 0, NULL, NULL);
	err = clEnqueueReadBuffer(f->cl.queue, f->cl.img, CL_TRUE, 0,
	sizeof(int) * WIDTH * HEIGHT, f->mlx.data, 0, NULL, NULL);
	mlx_put_image_to_window(f->mlx.mlx, f->mlx.win, f->mlx.img, 0, 0);
}
