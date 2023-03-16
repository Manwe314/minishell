/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:15:02 by lkukhale          #+#    #+#             */
/*   Updated: 2022/11/17 17:14:19 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char const *s1)
{
	int		size;
	char	*copy;
	int		i;
	char	*s;

	s = (char *)s1;
	size = (int)ft_strlen(s1);
	copy = (char *)malloc((size + 1) * sizeof(char));
	if (!copy)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
