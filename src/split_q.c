/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_q.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:40:46 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/15 21:41:16 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_size_q(char *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && !is_quoted(s, i))
			break ;
		size++;
		i++;
	}
	return (size);
}

int	word_count_q(char *s, char c)
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
			size = word_size_q(s, c, i);
			count++;
			i += size;
		}
		if (s[i] != '\0')
			i++;
	}
	return (count);
}

char	*make_string_q(char *s, int i, int size)
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

void	make_strings_q(char *s, char c, char **strings)
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
			size = word_size_q(s, c, i);
			strings[j] = make_string_q(s, i, size);
			j++;
			i += size;
		}
		if (s[i] != '\0')
			i++;
	}
	strings[j] = 0;
}

char	**ft_split_q(char *s, char c)
{
	char	**strings;
	int		words;

	if (!s)
		return (0);
	words = word_count_q(s, c);
	strings = (char **)malloc((words + 1) * sizeof(char *));
	if (!strings)
		return (0);
	make_strings_q(s, c, strings);
	return (strings);
}