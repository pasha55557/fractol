/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:01:51 by rsticks           #+#    #+#             */
/*   Updated: 2019/09/28 20:06:59 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	ft_init_cl(t_fractol *fractol)
{
	int		error;
	char	*kernel_str;
	size_t	kernel_len;
	cl_mem	d_mem;
	cl_mem	img;
	cl_mem	i_mem;
	int		intmem[32];
	double	dmem[32];
	size_t	global_work_size;

	error = clGetPlatformIDs(1, &fractol->cl.plat_id, &fractol->cl.num_platforms);
	error = clGetDeviceIDs(fractol->cl.plat_id, CL_DEVICE_TYPE_GPU, 1, &fractol->cl.dev_id, &fractol->cl.num_device);
	fractol->cl.context = clCreateContext(NULL, 1, &fractol->cl.dev_id, NULL, NULL, &error);
	fractol->cl.queue = clCreateCommandQueue(fractol->cl.context, fractol->cl.dev_id, 0, &error);
	/* место для чтения kernel */
	fractol->cl.prog = clCreateProgramWithSource(fractol->cl.context, 1, kernel_str, kernel_len, error);
	error = clBuildProgram(fractol->cl.prog, 1, fractol->cl.dev_id, NULL, NULL, NULL);
	fractol->cl.kernel = clCreateKernel(fractol->cl.prog, "start", &error);
	d_mem = clCreateBuffer(fractol->cl.context, CL_MEM_READ_WRITE, sizeof(double) * 32, NULL, &error);
	img = clCreateBuffer(fractol->cl.context, CL_MEM_READ_WRITE, sizeof(int) * WIDTH * HEIGHT, NULL, &error);
	i_mem = clCreateBuffer(fractol->cl.context, CL_MEM_READ_WRITE, sizeof(int) * 32, NULL, &error);
	error = clSetKernelArg(fractol->cl.kernel, 0, sizeof(cl_mem), &i_mem);
	error = clSetKernelArg(fractol->cl.kernel, 1, sizeof(cl_mem), &d_mem);
	error = clSetKernelArg(fractol->cl.kernel, 2, sizeof(cl_mem), &img);
	
	dmem[2] = fractol->min.im;
	dmem[3] = fractol->min.re;
	dmem[4] = fractol->max.im;
	dmem[5] = fractol->max.re;
	intmem[6] = fractol->id;
	intmem[7] = WIDTH;
	intmem[8] = HEIGHT;
	global_work_size = WIDTH * HEIGHT;
	error = clEnqueueWriteBuffer(fractol->cl.queue, i_mem, CL_TRUE, 0, sizeof(int) * 32, intmem, 0, NULL, NULL);
	error = clEnqueueWriteBuffer(fractol->cl.queue, d_mem, CL_TRUE, 0, sizeof(double) * 32, dmem, 0, NULL, NULL);
	error = clEnqueueNDRangeKernel(fractol->cl.queue, fractol->cl.kernel, 1, NULL, global_work_size, NULL, 0, NULL, NULL);
	error = clEnqueueReadBuffer(fractol->cl.queue, img, CL_TRUE, 0, sizeof(int) * WIDTH * HEIGHT, fractol->mlx.data, 0, NULL, NULL);
}