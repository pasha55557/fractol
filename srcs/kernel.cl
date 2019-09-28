/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:04:09 by rsticks           #+#    #+#             */
/*   Updated: 2019/09/26 15:25:12 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct			s_im
{
	double				im;
	double				re;
}						t_im;

typedef struct			s_fractol
{
	double				max_im;
	double				max_re;
	double				min_im;
	double				min_re;
	double				factor_im;
	double				factor_re;
	int					x;
	int					y;
	int					id;
	int					WIDTH;
	int					HEIGHT;
}						t_fractol;

__kernel void start(__global int *i_mem, __global double *d_mem, __global int *img)
{
	t_fractol	fractol;
	int			gid;

	gid = get_global_id(0); // номер пикселя
	fractol.WIDTH = i_mem[7];
	fractol.HEIGHT = i_mem[8];
	fractol.max_im = d_mem[4];
	fractol.max_re = d_mem[5];
	fractol.min_im = d_mem[2];
	fractol.min_re = d_mem[3];
}