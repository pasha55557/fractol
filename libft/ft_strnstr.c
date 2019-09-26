/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:19:08 by rsticks           #+#    #+#             */
/*   Updated: 2019/04/12 20:36:43 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	size_t a;
	size_t b;

	a = 0;
	while ((str1[a] != '\0') && (a != len))
	{
		b = 0;
		while (str1[a + b] == str2[b])
		{
			if ((str2[b + 1] == '\0') && ((a + b) < len))
				return ((char*)str1 + a);
			else
				b++;
		}
		a++;
	}
	if (str2[0] == '\0')
		return ((char*)str1);
	return (0);
}
