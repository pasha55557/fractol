/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:01:51 by rsticks           #+#    #+#             */
/*   Updated: 2019/10/08 19:23:28 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

static void		mem_to_kernel(double *dmem, int *intmem, t_fractol *fractol)
{
	dmem[0] = fractol->min.im;
	dmem[1] = fractol->min.re;
	dmem[2] = fractol->max.im;
	dmem[3] = fractol->max.re;
	dmem[4] = fractol->k.re;
	dmem[5] = fractol->k.im;
	intmem[0] = fractol->b;
	intmem[1] = fractol->g;
	intmem[2] = fractol->r;
	intmem[3] = fractol->max_iter;
	intmem[4] = fractol->id;
	intmem[5] = WIDTH;
	intmem[6] = HEIGHT;
}

static void		init_cl_two(t_fractol *fractol, int error)
{
	int 		i;
	int 		fd;
	char		*kernel_str;
	size_t		kernel_len;

	fd = open("kernel.cl", O_RDONLY);
	kernel_str = (char*)malloc(sizeof(char) * 5970);
	i = read(fd, kernel_str, 5970);
	kernel_str[i] = '\0';
	kernel_len = ft_strlen(kernel_str);
	fractol->cl.prog = clCreateProgramWithSource(fractol->cl.context, 1, (const char**)&kernel_str, &kernel_len, &error);
	error = clBuildProgram(fractol->cl.prog, 1, fractol->cl.dev_id, NULL, NULL, NULL);
	fractol->cl.kernel = clCreateKernel(fractol->cl.prog, "start", &error);
	fractol->cl.d_mem = clCreateBuffer(fractol->cl.context, CL_MEM_READ_WRITE, sizeof(double) * 6, NULL, &error);
	fractol->cl.img = clCreateBuffer(fractol->cl.context, CL_MEM_READ_WRITE, sizeof(int) * WIDTH * HEIGHT, NULL, &error);
	fractol->cl.i_mem = clCreateBuffer(fractol->cl.context, CL_MEM_READ_WRITE, sizeof(int) * 7, NULL, &error);
	error = clSetKernelArg(fractol->cl.kernel, 0, sizeof(cl_mem), &fractol->cl.i_mem);
	error = clSetKernelArg(fractol->cl.kernel, 1, sizeof(cl_mem), &fractol->cl.d_mem);
	error = clSetKernelArg(fractol->cl.kernel, 2, sizeof(cl_mem), &fractol->cl.img);
	start_kernel(fractol);
	ft_strdel(&kernel_str);
}

void			init_cl(t_fractol *fractol)
{
	int			error;

	error = clGetPlatformIDs(0, NULL, &fractol->cl.num_platforms);
	fractol->cl.plat_id = (cl_platform_id *)malloc(sizeof(cl_platform_id) * fractol->cl.num_platforms);
	error = clGetPlatformIDs(fractol->cl.num_platforms, fractol->cl.plat_id, NULL);
	error = clGetDeviceIDs(fractol->cl.plat_id[0], CL_DEVICE_TYPE_GPU, 0, NULL, &fractol->cl.num_device);
	fractol->cl.dev_id = (cl_device_id *)malloc(sizeof(cl_device_id) * fractol->cl.num_device);
	error = clGetDeviceIDs(fractol->cl.plat_id[0], CL_DEVICE_TYPE_GPU, fractol->cl.num_device, fractol->cl.dev_id, NULL);
	fractol->cl.context = clCreateContext(NULL, 1, fractol->cl.dev_id, NULL, NULL, &error);
	fractol->cl.queue = clCreateCommandQueue(fractol->cl.context, fractol->cl.dev_id[0], 0, &error);
	init_cl_two(fractol, error);
}

void			start_kernel(t_fractol *fractol)
{
	int 		error;
	double		dmem[6];
	int			intmem[7];
	size_t		global_work_size;

	mem_to_kernel(dmem, intmem, fractol);
	global_work_size = WIDTH * HEIGHT;
	error = clEnqueueWriteBuffer(fractol->cl.queue, fractol->cl.i_mem, CL_TRUE, 0, sizeof(int) * 7, intmem, 0, NULL, NULL);
	error = clEnqueueWriteBuffer(fractol->cl.queue, fractol->cl.d_mem, CL_TRUE, 0, sizeof(double) * 6, dmem, 0, NULL, NULL);
	error = clEnqueueNDRangeKernel(fractol->cl.queue, fractol->cl.kernel, 1, NULL, &global_work_size, NULL, 0, NULL, NULL);
	error = clEnqueueReadBuffer(fractol->cl.queue, fractol->cl.img, CL_TRUE, 0, sizeof(int) * WIDTH * HEIGHT, fractol->mlx.data, 0, NULL, NULL);
	mlx_put_image_to_window(fractol->mlx.mlx, fractol->mlx.win, fractol->mlx.img, 0, 0);
}