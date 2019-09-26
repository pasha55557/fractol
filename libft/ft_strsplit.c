/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 16:11:13 by rsticks           #+#    #+#             */
/*   Updated: 2019/04/18 20:08:39 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count(const char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		i++;
	}
	return (count);
}

static char		**ft_free(int i, char **res)
{
	while ((i - 1) != 0)
		free(res[i]);
	return (0);
}

static int		ft_split_size(const char *s, char c, int i)
{
	int	j;

	while (s[i] && s[i] == c)
		i++;
	j = i;
	while (s[j] != c && s[j])
		j++;
	return (j - i);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i[3];
	char	**res;

	i[0] = 0;
	i[1] = 0;
	if (!s)
		return (0);
	if (!(res = (char**)malloc(sizeof(char*) * ft_count(s, c) + 1)))
		return (0);
	while (s[i[0]] && i[1] < ft_count(s, c))
	{
		i[2] = 0;
		while (s[i[0]] == c)
			i[0]++;
		res[i[1]] = ft_strnew(ft_split_size(s, c, i[0]));
		if (res[i[1]] == NULL)
			return (ft_free(i[1], res));
		while (s[i[0]] != c && s[i[0]])
			res[i[1]][i[2]++] = s[i[0]++];
		res[i[1]++][i[2]] = '\0';
	}
	res[i[1]] = 0;
	return (res);
}
