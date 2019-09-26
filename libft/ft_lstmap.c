/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:06:51 by rsticks           #+#    #+#             */
/*   Updated: 2019/04/18 17:46:06 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*list[2];

	list[0] = f(lst);
	if (list[0] == NULL)
		return (0);
	list[1] = list[0];
	while (lst->next)
	{
		lst = lst->next;
		list[1]->next = f(lst);
		if (list[1]->next == NULL)
			return (0);
		list[1] = list[1]->next;
	}
	return (list[0]);
}
