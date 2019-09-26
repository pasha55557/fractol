/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:14:40 by rsticks           #+#    #+#             */
/*   Updated: 2019/04/15 14:20:30 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	unsigned char *str;

	str = (unsigned char*)destination;
	while (n--)
	{
		*str = (unsigned char)c;
		if (n)
			str++;
	}
	return (destination);
}
