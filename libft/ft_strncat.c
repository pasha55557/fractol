/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:51:12 by rsticks           #+#    #+#             */
/*   Updated: 2019/04/11 14:21:05 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncat(char *dst, const char *append, size_t n)
{
	int		i;
	int		j;
	size_t	g;

	g = 0;
	i = 0;
	j = 0;
	while (dst[i] != '\0')
		i++;
	while ((append[j] != '\0') && (g < n))
	{
		dst[i] = append[j];
		j++;
		i++;
		g++;
	}
	dst[i] = '\0';
	return (dst);
}
