/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 16:46:44 by rsticks           #+#    #+#             */
/*   Updated: 2019/04/21 14:54:27 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						ft_atoi(const char *str)
{
	struct s_atoi a;

	a.nb = 0;
	a.m = 1;
	a.i = 0;
	a.g = 0;
	while (str[a.i] == '\t' || str[a.i] == '\n' || str[a.i] == '\v'
			|| str[a.i] == '\f' || str[a.i] == ' '
			|| str[a.i] == '\r')
		a.i++;
	if (str[a.i] == '-' || str[a.i] == '+')
		if (str[a.i++] == '-')
			a.m = -1;
	while (str[a.i + a.g] >= '0' && str[a.i + a.g] <= '9')
	{
		a.nb = a.nb * 10 + (str[a.i + a.g] - '0');
		a.g++;
	}
	if ((a.nb <= 9223372036854775807) && (a.g <= 19))
		return (((int)a.nb) * a.m);
	else if (a.m > 0)
		return (-1);
	return (0);
}
