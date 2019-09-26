/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:55:07 by rsticks           #+#    #+#             */
/*   Updated: 2019/04/11 16:13:15 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t a;
	size_t b;
	size_t res;

	a = 0;
	b = 0;
	while (dst[a] != '\0')
		a++;
	while (src[b] != '\0')
		b++;
	if (size > a)
		res = a + b;
	else
		res = size + b;
	b = 0;
	while ((src[b] != '\0') && (a + 1 < size))
	{
		dst[a] = src[b];
		a++;
		b++;
	}
	dst[a] = '\0';
	return (res);
}
