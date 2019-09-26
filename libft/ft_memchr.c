/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:44:37 by rsticks           #+#    #+#             */
/*   Updated: 2019/04/11 11:54:26 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *dd, int cc, size_t n)
{
	size_t			i;
	unsigned char	c;
	unsigned char	*d;

	c = ((unsigned char)cc);
	d = ((unsigned char*)dd);
	i = 0;
	while (i < n)
	{
		if (*(d++) == c)
			return ((void*)--d);
		i++;
	}
	return (0);
}
