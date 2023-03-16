/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:40:43 by lkukhale          #+#    #+#             */
/*   Updated: 2023/03/16 19:07:23 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strchrgnl(char *s, char c)
{
	int		i;
	char	*str;
	char	c1;

	str = (char *)s;
	c1 = c;
	i = 0;
	if (!s)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c1)
			return (1);
		i++;
	}
	if (str[i] == c1)
		return (1);
	return (0);
}

char	*ft_strjoingnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (0);
	str = malloc((ft_strlengnl(s1) + ft_strlengnl(s2) + 1) * sizeof(char));
	if (str == 0)
		return (0);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[ft_strlengnl(s1) + ft_strlengnl(s2)] = '\0';
	free(s1);
	return (str);
}

int	ft_strlengnl(char *str)
{
	int	i;

	i = 0;
	if (str == 0)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}
