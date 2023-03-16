/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:08:12 by lkukhale          #+#    #+#             */
/*   Updated: 2022/11/21 19:15:15 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*start;

	if (!lst || !f)
		return (0);
	start = 0;
	while (lst)
	{
		newlist = ft_lstnew(f(lst->content));
		if (!newlist)
		{
			ft_lstclear(&start, del);
		}
		ft_lstadd_back(&start, newlist);
		lst = lst->next;
	}
	return (start);
}
