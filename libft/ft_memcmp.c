/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:12:44 by rsticks           #+#    #+#             */
/*   Updated: 2019/04/11 12:34:18 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *buf1, const void *buf2, size_t count)
{
	size_t			i;
	unsigned char	*b1;
	unsigned char	*b2;

	b1 = ((unsigned char*)buf1);
	b2 = ((unsigned char*)buf2);
	i = 0;
	while (i < count)
	{
		if (b1[i] != b2[i])
			return ((int)(b1[i] - b2[i]));
		i++;
	}
	return (0);
}
