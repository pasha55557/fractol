/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 12:33:25 by rsticks           #+#    #+#             */
/*   Updated: 2019/04/15 12:37:12 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	int c[10];
	int i;
	int minus;

	i = 0;
	minus = 1;
	if (nb == 0)
		ft_putchar_fd('0', fd);
	if (nb < 0)
	{
		minus = -1;
		ft_putchar_fd('-', fd);
	}
	while (nb != 0)
	{
		c[i] = (nb % 10) * minus;
		i++;
		nb = nb / 10;
	}
	while (i-- > 0)
		ft_putchar_fd(c[i] + '0', fd);
}
