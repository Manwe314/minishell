/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:13:36 by lkukhale          #+#    #+#             */
/*   Updated: 2022/11/17 19:28:50 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size1;
	int		size2;
	int		i;
	char	*joint;

	if (s1 && s2)
	{
		size1 = (int)ft_strlen(s1);
		size2 = (int)ft_strlen(s2);
		joint = (char *)malloc((size1 + size2 + 1) * sizeof(char));
		if (joint == 0)
			return (0);
		i = -1;
		while (s1[++i])
			joint[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			joint[size1] = s2[i];
			size1++;
		}
		joint[size1] = '\0';
		return (joint);
	}
	return (0);
}
