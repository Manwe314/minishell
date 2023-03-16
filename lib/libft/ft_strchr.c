/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:27:02 by lkukhale          #+#    #+#             */
/*   Updated: 2022/11/16 17:14:56 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;
	char	c1;

	str = (char *)s;
	c1 = (char)c;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c1)
			return (&str[i]);
		i++;
	}
	if (str[i] == c1)
		return (&str[i]);
	return (0);
}
