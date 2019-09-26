/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:01:51 by rsticks           #+#    #+#             */
/*   Updated: 2019/09/26 16:23:25 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	init_cl(t_fractol *fractol)
{
	int		r;
	char	*kernel_str;
	size_t	kernel_len;

	r = clGetPlatformIDs(1, &fractol->cl.plat_id, &fractol->cl.num_platforms);
	r = clGetDeviceIDs(fractol->cl.plat_id, CL_DEVICE_TYPE_GPU, 1, &fractol->cl.dev_id, fractol->cl.num_device);
	fractol->cl.cont = clCreateContext(NULL, 1, &fractol->cl.dev_id, NULL, NULL, &r);
	fractol->cl.queue = clCreateCommandQueue(fractol->cl.cont, fractol->cl.dev_id, 0, &r);

}