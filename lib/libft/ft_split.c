/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:33:07 by lkukhale          #+#    #+#             */
/*   Updated: 2022/12/16 15:31:47 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	word_size(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			break ;
		size++;
		i++;
	}
	return (size);
}

int	word_count(char const *s, char c)
{
	int	i;
	int	count;
	int	size;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			size = word_size(s, c, i);
			count++;
			i += size;
		}
		if (s[i] != '\0')
			i++;
	}
	return (count);
}

char	*make_string(char const *s, int i, int size)
{
	char	*ptr;
	int		j;

	ptr = (char *)malloc(sizeof(char) * (size + 1));
	if (!ptr)
		return (0);
	j = 0;
	while (j < size)
	{
		ptr[j] = s[i + j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

void	make_strings(char const *s, char c, char **strings)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			size = word_size(s, c, i);
			strings[j] = make_string(s, i, size);
			j++;
			i += size;
		}
		if (s[i] != '\0')
			i++;
	}
	strings[j] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**strings;
	int		words;

	if (!s)
		return (0);
	words = word_count(s, c);
	strings = (char **)malloc((words + 1) * sizeof(char *));
	if (!strings)
		return (0);
	make_strings(s, c, strings);
	return (strings);
}
