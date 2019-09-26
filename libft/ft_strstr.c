/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:51:29 by rsticks           #+#    #+#             */
/*   Updated: 2019/04/12 19:15:53 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *str1, const char *str2)
{
	int a;
	int b;

	a = 0;
	while (str1[a] != '\0')
	{
		b = 0;
		while (str1[a + b] == str2[b])
		{
			if (str2[b + 1] == '\0')
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
