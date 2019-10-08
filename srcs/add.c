/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:45:07 by rsticks           #+#    #+#             */
/*   Updated: 2019/10/08 19:22:57 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

t_im	init_complex(double re, double im)
{
	t_im comp;

	comp.im = im;
	comp.re = re;
	return(comp);
}
