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

/*typedef struct			s_im
{
	double				im;
	double				re;
}						t_im;
*/
typedef struct			s_fractol
{
	double				max_im;
	double				max_re;
	double				min_im;
	double				min_re;
	double				factor_re;
	double				factor_im;
	int					x;
	int					y;
	int					id;
	int					WIDTH;
	int					HEIGHT;
	int					gid;
}						t_fractol;

int		set_color(double t);
void	fractol_mandelbrot(t_fractol fractol, __global int *img);
/*t_im	init_complex(double re, double im)
{
	t_im comp;

	comp.im = im;
	comp.re = re;
	return(comp);
}*/

int		set_color(double t)
{
	int r;
	int g;
	int b;

	r = (int)(9 * (1 - t) * pow(t, 3) * 255);
	g = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
	b = (int)(8.5 * pow((1 - t), 3) * t * 255);
	return ((b << 16) | (g << 8) | r);
}

void	fractol_mandelbrot(t_fractol fractol, __global int *img)
{
	int		max_iter;
	int		iter;
	double	t;
	int		rgb;
	double	z_im;
	double	z_re;
	double	c_im;
	double	c_re;

	fractol.factor_re = (fractol.max_re - fractol.min_re) / (fractol.WIDTH - 1); 
	fractol.factor_im = (fractol.max_im - fractol.min_im) / (fractol.HEIGHT - 1);
	max_iter = 150;
	c_re = fractol.min_re + fractol.x * fractol.factor_re;
	c_im = fractol.max_im - fractol.y * fractol.factor_im;
	z_re = c_re;
	z_im = c_im;
	iter = 0;
	while (pow(z_re, 2.0) + pow(z_im, 2.0) <= 4 && iter < max_iter)
	{
		z_re = pow(z_re, 2.0) - pow(z_im, 2.0) + c_re;
		z_im = 2.0 * z_re * z_im + c_im;
		iter++;
	}
	t = (double)iter / (double)max_iter;
	rgb = set_color(t);
	//if (fractol.x >= 0 && fractol.x < fractol.WIDTH && fractol.y >= 0 && fractol.y < fractol.HEIGHT) */
	img[fractol.x + (fractol.y * fractol.WIDTH)] = rgb;
	
}

__kernel void start(__global int *i_mem, __global double *d_mem, __global int *img)
{
	t_fractol	fractol;
	int			id;

	id = get_global_id(0);
	fractol.gid = id;
	fractol.WIDTH = i_mem[7];
	fractol.HEIGHT = i_mem[8];
	fractol.y = id / fractol.WIDTH;
	fractol.x = id % fractol.WIDTH;
	fractol.max_re = d_mem[5];
	fractol.min_re = d_mem[3];
	fractol.min_im = d_mem[2];
	fractol.max_im = d_mem[4];
	fractol.id = i_mem[6];
	fractol_mandelbrot(fractol, img);
	//if (fractol.y == 5 && fractol.x >= 0 && fractol <= 1920)
	//img[fractol.x + (fractol.y * fractol.WIDTH)] = 0xFFFFFF;
}