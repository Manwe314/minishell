/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:04:32 by lkukhale          #+#    #+#             */
/*   Updated: 2022/11/17 15:41:37 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int		i;
	unsigned char		*ptrdst;
	unsigned const char	*ptrsrc;

	if (!dst && !src)
		return (0);
	i = 0;
	ptrdst = (unsigned char *)dst;
	ptrsrc = (unsigned const char *)src;
	while (i < n)
	{
		*((char *)ptrdst + i) = *((char *)ptrsrc + i);
		i++;
	}
	return (ptrdst);
}
