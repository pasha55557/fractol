/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:53:07 by rsticks           #+#    #+#             */
/*   Updated: 2019/04/18 19:03:54 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strtrim_2(int i, int j, char const *s)
{
	j = i;
	while (s[++j] != '\0')
		;
	j--;
	while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
		j--;
	return (j);
}

char	*ft_strtrim(char const *s)
{
	int		i[3];
	char	*str;

	i[0] = 0;
	i[2] = 0;
	if (!s)
		return (0);
	while (s[i[0]] == ' ' || s[i[0]] == '\n' || s[i[0]] == '\t')
		i[0]++;
	if (s[i[0]] == '\0')
		return (ft_strnew(0));
	i[1] = ft_strtrim_2(i[0], i[1], s);
	str = ft_strnew(i[1] - i[0] + 1);
	if (str == NULL)
		return (str);
	while (i[0] != (i[1] + 1))
	{
		str[i[2]] = s[i[0]++];
		i[2]++;
	}
	str[i[2]] = '\0';
	return (str);
}
