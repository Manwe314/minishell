/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 21:36:45 by lkukhale          #+#    #+#             */
/*   Updated: 2023/07/02 15:42:28 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_there(const char *haystack, const char *needle, size_t len, size_t i)
{
	size_t	id;
	int		cmp;

	id = 0;
	while (haystack[i + id] == needle[id] && (needle[id] != '\0'))
	{
		id++;
	}
	cmp = (int)id;
	if (cmp == (int)ft_strlen(needle))
	{
		if ((i + id) > len)
			return (0);
		else
			return (1);
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*hay;
	size_t	i;

	hay = (char *)haystack;
	if ((int)ft_strlen(needle) == 0)
		return (hay);
	i = 0;
	while (i < len && (haystack[i] != '\0'))
	{
		if (haystack[i] == needle[0])
		{
			if (is_there(haystack, needle, len, i))
				return (&hay[i]);
		}
		i++;
	}
	return (0);
}
