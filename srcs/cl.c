/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:01:51 by rsticks           #+#    #+#             */
/*   Updated: 2019/10/02 15:42:10 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

const char *hello = "__kernel void xer3(int xer, int xer2)				\
{																			\
	xer = 3;																\
	xer2 = 4;																\
}";																			


void	ft_init_cl(t_fractol *fractol)
{
	int		i;
	int		fd;
	int		error;
	char	*kernel_str;
	size_t	kernel_len;
	char	test[1024];

	error = clGetPlatformIDs(NULL, NULL, &fractol->cl.num_platforms);
	printf("init cl %d\n", error);
	fractol->cl.plat_id = (cl_platform_id *)malloc(sizeof(cl_platform_id) * fractol->cl.num_platforms);
	error = clGetPlatformIDs(fractol->cl.num_platforms, fractol->cl.plat_id, NULL);
	clGetPlatformInfo(fractol->cl.plat_id[0], CL_PLATFORM_NAME, 1024, test, NULL);
	printf("platform id %s\n", test);
	error = clGetDeviceIDs(fractol->cl.plat_id[0], CL_DEVICE_TYPE_GPU, 0, NULL, &fractol->cl.num_device);
	fractol->cl.dev_id = (cl_device_id *)malloc(sizeof(cl_device_id) * fractol->cl.num_device);
	error = clGetDeviceIDs(fractol->cl.plat_id[0], CL_DEVICE_TYPE_GPU, fractol->cl.num_device, fractol->cl.dev_id, NULL);
	printf("num device %d\n", fractol->cl.num_device);
	clGetDeviceInfo(fractol->cl.dev_id[0], CL_DEVICE_NAME, 1024, test, NULL);
	printf("Device id %s\n", test);
	//exit(0);
	
	printf("clGetDeviceIDs %d\n", error);
	fractol->cl.context = clCreateContext(NULL, 1, fractol->cl.dev_id, NULL, NULL, &error);
	printf("clCreateContext %d\n", error);
	fractol->cl.queue = clCreateCommandQueue(fractol->cl.context, fractol->cl.dev_id[0], 0, &error);
	printf("CreateCommandQueue %d\n", error);
	fd = open("srcs/kernel.cl", O_RDONLY);
	kernel_str = (char*)malloc(sizeof(char) * 10000);
	i = read(fd, kernel_str, 10000);
	kernel_str[i] = '\0';
	kernel_len = ft_strlen(kernel_str);
	//printf("%s", kernel_str);
	
	fractol->cl.prog = clCreateProgramWithSource(fractol->cl.context, 1, (const char**)&kernel_str, &kernel_len, &error);
	printf("CreateProgramWithSource %d\n", error);
	error = clBuildProgram(fractol->cl.prog, 1, fractol->cl.dev_id, NULL, NULL, NULL);
	int hello;
	clGetProgramBuildInfo(fractol->cl.prog, fractol->cl.dev_id[0], CL_PROGRAM_BUILD_LOG, 0, NULL, &hello);
	clGetProgramBuildInfo(fractol->cl.prog, fractol->cl.dev_id[0], CL_PROGRAM_BUILD_LOG, hello, test, NULL);
	printf("%s\n", test);
	printf("clBuildProgram %d\n", error);
	//exit(1);
	fractol->cl.kernel = clCreateKernel(fractol->cl.prog, "start", &error);
	printf("clCreateKernel %d\n", error);
	fractol->cl.d_mem = clCreateBuffer(fractol->cl.context, CL_MEM_READ_WRITE, sizeof(double) * 32, NULL, &error);
	printf("clCreateBuffer %d\n", error);
	fractol->cl.img = clCreateBuffer(fractol->cl.context, CL_MEM_READ_WRITE, sizeof(int) * WIDTH * HEIGHT, NULL, &error);
	printf("clCreateBuffer %d\n", error);
	fractol->cl.i_mem = clCreateBuffer(fractol->cl.context, CL_MEM_READ_WRITE, sizeof(int) * 32, NULL, &error);
	printf("clCreateBuffer %d\n", error);
	error = clSetKernelArg(fractol->cl.kernel, 0, sizeof(cl_mem), &fractol->cl.i_mem);
	printf("clSetKernelArg %d\n", error);
	error = clSetKernelArg(fractol->cl.kernel, 1, sizeof(cl_mem), &fractol->cl.d_mem);
	printf("clSetKernelArg %d\n", error);
	error = clSetKernelArg(fractol->cl.kernel, 2, sizeof(cl_mem), &fractol->cl.img);
	printf("clSetKernelArg %d\n\n", error);
	start_kernel(fractol);
	ft_strdel(&kernel_str);
}

void	start_kernel(t_fractol *fractol)
{
	int 		error;
	double		dmem[32];
	int			intmem[32];
	size_t		global_work_size;

	dmem[2] = fractol->min.im;
	dmem[3] = fractol->min.re;
	dmem[4] = fractol->max.im;
	dmem[5] = fractol->max.re;
	dmem[6] = fractol->k.re;
	dmem[7] = fractol->k.im;
	intmem[6] = fractol->id;
	intmem[7] = WIDTH;
	intmem[8] = HEIGHT;
	global_work_size = WIDTH * HEIGHT;
	error = clEnqueueWriteBuffer(fractol->cl.queue, fractol->cl.i_mem, CL_TRUE, 0, sizeof(int) * 32, intmem, 0, NULL, NULL);
	error = clEnqueueWriteBuffer(fractol->cl.queue, fractol->cl.d_mem, CL_TRUE, 0, sizeof(double) * 32, dmem, 0, NULL, NULL);
	error = clEnqueueNDRangeKernel(fractol->cl.queue, fractol->cl.kernel, 1, NULL, &global_work_size, NULL, 0, NULL, NULL);
	error = clEnqueueReadBuffer(fractol->cl.queue, fractol->cl.img, CL_TRUE, 0, sizeof(int) * WIDTH * HEIGHT, fractol->mlx.data, 0, NULL, NULL);
	mlx_put_image_to_window(fractol->mlx.mlx, fractol->mlx.win, fractol->mlx.img, 0, 0);
}