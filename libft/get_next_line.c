/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:34:17 by rsticks           #+#    #+#             */
/*   Updated: 2019/06/03 18:59:52 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

void				ft_join(char ***line, char **buf)
{
	char	*temp;

	if (**buf == '\0')
		return ;
	temp = **line;
	**line = ft_strjoin(**line, *buf);
	free(temp);
}

void				nachalo(char **buf, char ***line, char **ost_tab)
{
	*buf = ft_strnew(BUFF_SIZE);
	**line = ft_strnew(0);
	if (*ost_tab != NULL)
	{
		*buf = ft_strcpy(*buf, *ost_tab);
		ft_strdel(&*ost_tab);
	}
}

int					next_line(int x, char **buf, char ***line, char **ost_tab)
{
	char	*temp;
	char	*buf2;

	buf2 = ft_strnew(x);
	buf2 = ft_strncpy(buf2, *buf, x);
	ft_join(&*line, &buf2);
	temp = ft_strchr(*buf, '\n');
	*ost_tab = ft_strnew(ft_strlen(++temp));
	*ost_tab = ft_strcpy(*ost_tab, temp);
	ft_strdel(&*buf);
	ft_strdel(&buf2);
	return (1);
}

int					last_line(char ***line, char **buf, int fd)
{
	int	i;

	ft_join(&*line, &*buf);
	ft_bzero(*buf, BUFF_SIZE + 1);
	i = read(fd, *buf, BUFF_SIZE);
	if (i <= 0)
	{
		ft_strdel(&*buf);
		if (**line && ***line != '\0')
			return (1);
		else
			return (i);
	}
	else
		return (++i);
}

int					get_next_line(const int fd, char **line)
{
	struct s_gnl	a;
	static char		*ost_tab[10241];

	if (fd < 0 || fd > 10240 || !line)
		return (-1);
	nachalo(&a.buf, &line, &ost_tab[fd]);
	a.if_n = 0;
	while (a.if_n == 0)
	{
		a.x = 0;
		while ((a.buf[a.x] != '\0') && (a.buf[a.x] != '\n'))
			a.x++;
		if (a.buf[a.x] == '\n')
			a.if_n = next_line(a.x, &a.buf, &line, &ost_tab[fd]);
		else if (a.buf[a.x] == '\0')
			if ((a.i = last_line(&line, &a.buf, fd)) <= 1)
				return (a.i);
	}
	return (1);
}
