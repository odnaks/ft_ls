/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 14:33:47 by drestles          #+#    #+#             */
/*   Updated: 2019/03/14 17:34:21 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*oldlists;
	t_list	*newlists;
	t_list	*lists;

	if (!lst || !f)
		return (NULL);
	oldlists = lst;
	newlists = f(oldlists);
	if (!newlists)
		return (NULL);
	lists = newlists;
	while (oldlists->next)
	{
		oldlists = oldlists->next;
		newlists->next = f(oldlists);
		newlists = newlists->next;
		if (!newlists)
			return (NULL);
	}
	return (lists);
}
