/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 16:33:14 by rsticks           #+#    #+#             */
/*   Updated: 2019/04/10 18:15:58 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dest, const void *source, int ch, size_t count)
{
	size_t			i;
	unsigned char	c;

	c = ((unsigned char)ch);
	i = 0;
	while (i < count)
	{
		((unsigned char*)dest)[i] = ((unsigned char*)source)[i];
		if (((unsigned char*)source)[i] == c)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
