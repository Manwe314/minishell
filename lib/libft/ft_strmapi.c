/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:23:21 by lkukhale          #+#    #+#             */
/*   Updated: 2022/11/18 19:15:24 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	int				size;
	char			*output;
	char			*s1;

	if (!s)
		return (0);
	s1 = (char *)s;
	i = 0;
	size = (int)ft_strlen(s);
	output = (char *)malloc((size + 1) * sizeof(char));
	if (!output)
		return (0);
	while (s[i] != '\0')
	{
		output[i] = (*f)(i, s[i]);
		i++;
	}
	output[i] = '\0';
	return (output);
}
