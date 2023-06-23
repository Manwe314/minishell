/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hall <hall@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:37:21 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/23 22:18:33 by hall             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sub_check_rt_one(char *input, int i, int save)
{
	i++;
	while (input[i] != '\0' && input[i] == ' ')
		i++;
	if (input[i] == '<' || input[i] == '\0')
		return (1);
	if (input[i] == '>' && i == save)
	{
		i++;
		while (input[i] != '\0' && input[i] == ' ')
			i++;
		if (input[i] == '<' || input[i] == '\0' || input[i] == '>'
			|| input[i] == '|')
			return (1);
	}
	else if (input[i] == '>' && i != save)
		return (1);
	return (0);
}

int	sub_check_rt_two(char *input, int i, int save)
{
	i++;
	while (input[i] != '\0' && input[i] == ' ')
		i++;
	if (input[i] == '>' || input[i] == '\0')
		return (1);
	if (input[i] == '<' && i == save)
	{
		i++;
		while (input[i] != '\0' && input[i] == ' ')
			i++;
		if (input[i] == '<' || input[i] == '\0' || input[i] == '>'
			|| input[i] == '|')
			return (1);
	}
	else if (input[i] == '<' && i != save)
		return (1);
	return (0);
}

int	check_redirection_token(char *input, int i)
{
	int	save;

	save = i + 1;
	if (input[i] == '>')
	{
		if (sub_check_rt_one(input, i, save))
			return (1);
	}
	else if (input[i] == '<')
	{
		if (sub_check_rt_two(input, i, save))
			return (1);
	}
	return (0);
}
