/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:02:06 by lkukhale          #+#    #+#             */
/*   Updated: 2022/11/21 20:54:29 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	starter(char const *s1, char const *set, size_t *count)
{
	size_t	i;
	size_t	j;
	int		status;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
			{
				status = 0;
				(*count)++;
				break ;
			}
			else
				status = 1;
			j++;
		}
		if (status)
			break ;
		i++;
	}
	return ((unsigned int)i);
}

void	counter(char const *s1, char const *set, size_t *count)
{
	size_t	i;
	size_t	j;
	int		status;

	i = ft_strlen(s1) - 1;
	while (i >= 0)
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
			{
				status = 0;
				(*count)++;
				break ;
			}
			else
				status = 1;
			j++;
		}
		if (status)
			break ;
		i--;
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t			*count;
	size_t			amount;
	unsigned int	start;
	int				size;

	if (!s1 || !set || !ft_strlen(s1) || !ft_strlen(set))
		return (ft_strdup(s1));
	amount = 0;
	count = &amount;
	start = starter(s1, set, count);
	size = (int)ft_strlen(s1);
	counter(s1, set, count);
	if ((size - (int)amount) <= 0)
		return (ft_strdup(""));
	return (ft_substr(s1, start, (ft_strlen(s1) - amount)));
}
