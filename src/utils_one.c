/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:38:27 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/27 21:15:56 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_handler(char *msg, int flag)
{
	if (flag == 0)
	{
		if (msg != 0)
			printf("%s\n", msg);
		return (g_global.exit_status);
	}
	if (flag == 1)
	{
		perror(msg);
		g_global.error_status = 1;
		return (0);
	}
	if (flag == 2)
	{
		perror(msg);
		ft_putstr_fd("Fatal Error\n", g_global.save_stdout);
		g_global.error_status = 2;
		return (-1);
	}
	return (0);
}

int	is_quoted(char *input, int index)
{
	int	*quote_pairs;

	quote_pairs = find_quote_pairs(input, 0);
	if (quote_pairs[1] == 0)
		return (0);
	while (quote_pairs[1] != 0)
	{
		if (index > quote_pairs[0] && index < quote_pairs[1])
		{
			if (input[index] == '$' && input[quote_pairs[0]] == 34)
				return (0);
			else
				return (1);
		}
		quote_pairs = find_quote_pairs(input, quote_pairs[1] + 1);
	}
	return (0);
}

int	is_all_space(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (input == 0)
		return (0);
	while (input[i] != '\0')
	{
		if (input[i] == ' ' || input[i] == '	')
			j++;
		i++;
	}
	if (i == j)
		return (1);
	return (0);
}

int	*find_quote_pairs(char *input, int start)
{
	int			i;
	int			j;
	static int	quote_pair[2];

	i = start - 1;
	quote_pair[0] = 0;
	quote_pair[1] = 0;
	while (input[++i] != '\0')
	{
		if (input[i] == 39 || input[i] == 34)
		{
			j = i + 1;
			quote_pair[0] = i;
			while (input[j] != '\0' && input[i] != '\0')
			{
				if (input[j] == input[i])
				{
					quote_pair[1] = j;
					return (quote_pair);
				}
				j++;
			}
		}
	}
	return (quote_pair);
}
