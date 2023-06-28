/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:22:27 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/28 16:29:24 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		ft_strlengnl(char *str);
char	*ft_strjoingnl(char *s1, char *s2);

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

char	*save_the_state(char *current)
{
	int		i;
	int		j;
	char	*new_state;

	i = 0;
	while (current[i] != '\0' && current[i] != '\n')
		i++;
	if (!current[i])
	{
		free(current);
		return (0);
	}
	new_state = malloc(sizeof(char) * ft_strlengnl(current) - i + 1);
	if (!new_state)
		return (0);
	i++;
	j = 0;
	while (current[i] != '\0')
		new_state[j++] = current[i++];
	new_state[j] = '\0';
	free(current);
	return (new_state);
}

char	*give_the_line(char *current)
{
	int		i;
	char	*line;

	i = 0;
	if (!current[i])
		return (0);
	while (current[i] != '\0' && current[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (0);
	i = 0;
	while (current[i] != '\0' && current[i] != '\n')
	{
		line[i] = current[i];
		i++;
	}
	if (current[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}
