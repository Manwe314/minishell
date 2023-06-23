/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hall <hall@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:35:38 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/23 22:23:51 by hall             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_piping(char *input)
{
	int	i;
	int	is_piped;

	i = 0;
	is_piped = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '|' && !is_quoted(input, i))
		{
			is_piped = 1;
			break ;
		}
		i++;
	}
	return (is_piped);
}

int	initial_pipe_check(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ' && input[i] != '\0')
		i++;
	if (input[i] == '|')
		return (-1);
	i = ft_strlengnl(input);
	i--;
	while (i >= 0 && input[i] == ' ')
		i--;
	if (input[i] == '|')
		return (1);
	return (0);
}

int	is_open_quotes(char *input)
{
	int	*quote_pair;

	quote_pair = find_quote_pairs(input, 0);
	if (quote_pair[0] != 0 && quote_pair[1] == 0)
		return (1);
	while (quote_pair[0] != 0 && quote_pair[1] != 0)
	{
		quote_pair = find_quote_pairs(input, quote_pair[1] + 1);
		if (quote_pair[0] != 0 && quote_pair[1] == 0)
			return (1);
	}
	return (0);
}

int	check_pipe_token(char *input, int i)
{
	i++;
	while (input[i] != '\0' && input[i] == ' ')
		i++;
	if (input[i] == '|')
		return (1);
	if (initial_pipe_check(input) == -1)
		return (1);
	return (0);
}

int	validate_input(char *input)
{
	int	i;
	int	*quote_pair;

	i = 0;
	if (is_open_quotes(input))
		return (0);
	quote_pair = find_quote_pairs(input, 0);
	while (input[i] != '\0')
	{
		if (i == quote_pair[0] && quote_pair[1] != 0)
		{
			i = quote_pair[1];
			quote_pair = find_quote_pairs(input, quote_pair[1] + 1);
		}
		if (input[i] == '<' || input[i] == '>')
			if (check_redirection_token(input, i))
				return (0);
		if (input[i] == '|')
			if (check_pipe_token(input, i))
				return (0);
		i++;
	}
	return (1);
}
