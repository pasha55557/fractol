/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:19:54 by rsticks           #+#    #+#             */
/*   Updated: 2019/04/12 17:47:49 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *str, int ch)
{
	char *st;
	char chr;
	char *buf;

	buf = 0;
	st = ((char*)str);
	chr = ((char)ch);
	while (*st != '\0')
	{
		if (*st == chr)
			buf = st;
		st++;
	}
	if (buf)
		return (buf);
	if (chr == '\0')
		return (st);
	return (0);
}
