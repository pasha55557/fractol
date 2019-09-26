/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 19:29:39 by rsticks           #+#    #+#             */
/*   Updated: 2019/04/15 19:51:28 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (0);
	str = ft_strnew(len);
	if (str == NULL)
		return (0);
	i = 0;
	s = s + start;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}
