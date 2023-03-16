/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:39:53 by lkukhale          #+#    #+#             */
/*   Updated: 2022/11/17 16:02:07 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;
	unsigned char	*b1;
	unsigned char	*b2;

	b1 = (unsigned char *)s1;
	b2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (b1[i] != '\0' && b2[i] != '\0' && b1[i] == b2[i] && (i + 1) < n)
		i++;
	return (b1[i] - b2[i]);
}
