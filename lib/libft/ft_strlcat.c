/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:38:28 by lkukhale          #+#    #+#             */
/*   Updated: 2022/11/17 18:35:45 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dest;
	size_t	sorc;

	sorc = ft_strlen(src);
	if (!dst && dstsize == 0)
		return (sorc);
	i = 0;
	dest = ft_strlen(dst);
	if (!dstsize)
		return (sorc);
	while (src[i] != '\0' && dest + i < dstsize - 1)
	{
		dst[dest + i] = src[i];
		i++;
	}
	dst[dest + i] = '\0';
	if (dest > dstsize)
		return (sorc + dstsize);
	return (sorc + dest);
}
