/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 19:31:45 by rsticks           #+#    #+#             */
/*   Updated: 2019/04/21 15:46:03 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	char	*str;
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (src[count] != '\0')
		count++;
	str = (char*)malloc(sizeof(char) * (count + 1));
	if (str == NULL)
		return (NULL);
	while (i < count)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
