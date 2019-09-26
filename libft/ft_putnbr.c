/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 15:16:00 by rsticks           #+#    #+#             */
/*   Updated: 2019/04/10 13:45:04 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nb)
{
	int c[10];
	int i;
	int minus;

	i = 0;
	minus = 1;
	if (nb == 0)
		ft_putchar('0');
	if (nb < 0)
	{
		minus = -1;
		ft_putchar('-');
	}
	while (nb != 0)
	{
		c[i] = (nb % 10) * minus;
		i++;
		nb = nb / 10;
	}
	while (i-- > 0)
		ft_putchar(c[i] + '0');
}
