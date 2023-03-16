/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:42:59 by lkukhale          #+#    #+#             */
/*   Updated: 2022/11/16 14:56:06 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*ptr;

	if (!src && !dst)
		return (0);
	ptr = dst;
	if (src > dst)
	{
		while (len--)
		{
			*(unsigned char *)dst++ = *(unsigned char *)src++;
		}
	}
	else
	{
		dst += len;
		src += len;
		while (len--)
		{
			*(unsigned char *)(--dst) = *(unsigned char *)(--src);
		}
	}
	return (ptr);
}
