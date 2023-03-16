/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:11:15 by lkukhale          #+#    #+#             */
/*   Updated: 2022/11/21 19:23:21 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node;

	if (!lst || !del)
		return ;
	if (*lst)
	{
		while (*lst)
		{
			node = (*lst)->next;
			ft_lstdelone(*lst, del);
			(*lst) = node;
		}
	}
	*lst = 0;
}
