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
	double				factor_re;
	double				factor_im;
	int					x;
	int					y;
	int					id;
	int					WIDTH;
	int					HEIGHT;
	int					gid;
}						t_fractol;

int		set_color(double t, int	rc, int gc, int bc);
void	fractol_mandelbrot(t_fractol fractol, __global int *img);
t_im	init_complex(double re, double im);

t_im	init_complex(double re, double im)
{
	t_im comp;

	comp.im = im;
	comp.re = re;
	return(comp);
}

int		set_color(double t, int	rc, int gc, int bc)
{
	int r;
	int g;
	int b;

	r = (int)(8.5 * pow((1 - t), 3) * t * 255);
	g = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
	b = (int)(9 * (1 - t) * pow(t, 3) * 255);
	return (((r << rc) | (g << gc) | b << bc));
}

__kernel void start(__global int *i_mem, __global double *d_mem, __global int *img)
{
	t_fractol	fractol;
	int			id;
	t_im		k;
	t_im		c;
	t_im		z;
	int			iter;
	int			max_iter;
	double		t;
	int			rgb;
	int			r;
	int			g;
	int			b;

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
	k.re = d_mem[6];
	k.im = d_mem[7];
	max_iter = i_mem[5];
	r = i_mem[4];
	g = i_mem[3];
	b = i_mem[2];
	
	/* fractal mandelbrot */

	if (fractol.id == 1)
	{
		fractol.factor_re = (fractol.max_re - fractol.min_re) / (fractol.WIDTH - 1);
		fractol.factor_im = (fractol.max_im - fractol.min_im) / (fractol.HEIGHT - 1);
		c.im = fractol.max_im - fractol.y * fractol.factor_im;
		c.re = fractol.min_re + fractol.x * fractol.factor_re;
		z = init_complex(c.re, c.im);
		iter = 0;
		while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 256 && iter < max_iter)
		{
			z = init_complex((pow(z.re, 2.0) - pow(z.im, 2.0)) + c.re, 2.0 * z.re * z.im + c.im);
			// формула
			iter++;
		}
		if (iter == max_iter)
				rgb = 0;
		else
		{
			t = pow(((double)iter / (double)(max_iter)), 2.0);
			rgb = set_color(t, r, g, b);
		}
		img[fractol.gid] = rgb;
	}

	/* fractal julia */

	if (fractol.id == 2)
	{
		fractol.factor_re = (fractol.max_re - fractol.min_re) / (fractol.WIDTH - 1);
		fractol.factor_im = (fractol.max_im - fractol.min_im) / (fractol.HEIGHT - 1);
		c.im = fractol.max_im - fractol.y * fractol.factor_im;
		c.re = fractol.min_re + fractol.x * fractol.factor_re;
		z = init_complex(c.re, c.im);
		iter = 0;
		while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 256 && iter < max_iter)
		{
			z = init_complex((pow(z.re, 2.0) - pow(z.im, 2.0)) + k.re, 2.0 * z.re * z.im + k.im);
			iter++;
		}
		if (iter == max_iter)
			rgb = 0;
		else
		{
			t = pow(((double)iter / (double)(max_iter)), 2.0);
			rgb = set_color(t, r, g, b);
		}
		img[fractol.gid] = rgb;
	}

	/* fractal Burningship */

	if (fractol.id == 3)
	{
		fractol.factor_re = (fractol.max_re - fractol.min_re) / (fractol.WIDTH - 1);
		fractol.factor_im = (fractol.max_im - fractol.min_im) / (fractol.HEIGHT - 1);
		c.im = fractol.max_im - fractol.y * fractol.factor_im;
		c.re = fractol.min_re + fractol.x * fractol.factor_re;
		z = init_complex(c.re, c.im);
		iter = 0;
		while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 256 && iter < max_iter)
		{
    		z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0) + c.re, -2.0 * fabs(z.re * z.im) + c.im);
    		iter++;
		}
		if (iter == max_iter)
			rgb = 0;
		else
		{
			t = pow(((double)iter / (double)(max_iter)), 2.0);
			rgb = set_color(t, r, g, b);
		}
		img[fractol.gid] = rgb;
	}

	/* fractal Mandelbar */
	
	if (fractol.id == 4)
	{
		fractol.factor_re = (fractol.max_re - fractol.min_re) / (fractol.WIDTH - 1);
		fractol.factor_im = (fractol.max_im - fractol.min_im) / (fractol.HEIGHT - 1);
		c.im = fractol.max_im - fractol.y * fractol.factor_im;
		c.re = fractol.min_re + fractol.x * fractol.factor_re;
		z = init_complex(c.re, c.im);
		iter = 0;
		while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 && iter < max_iter)
		{
    		z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0) + c.re, -2.0 * z.re * z.im + c.im);
    		iter++;
		}
		if (iter == max_iter)
			rgb = 0;
		else
		{
			t = pow(((double)iter / (double)(max_iter)), 2.0);
			rgb = set_color(t, r, g, b);
		}
		img[fractol.gid] = rgb;
	}
		/* fractal tanhjulia */

	if (fractol.id == 5)
	{
		fractol.factor_re = (fractol.max_re - fractol.min_re) / (fractol.WIDTH - 1);
		fractol.factor_im = (fractol.max_im - fractol.min_im) / (fractol.HEIGHT - 1);
		c.im = fractol.max_im - fractol.y * fractol.factor_im;
		c.re = fractol.min_re + fractol.x * fractol.factor_re;
		z = init_complex(c.re, c.im);
		iter = 0;
		while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 256 && iter < max_iter)
		{
			z = init_complex(tanh(pow(z.re, 2.0) - pow(z.im, 2.0)) + k.re, 4.0 * z.re * z.im + k.im);
			iter++;
		}
		if (iter == max_iter)
			rgb = 0;
		else
		{
			t = pow(((double)iter / (double)(max_iter)), 2.0);
			rgb = set_color(t, r, g, b);
		}
		img[fractol.gid] = rgb;
	}
}
