/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hall <hall@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:53:32 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/23 22:14:20 by hall             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_after_redirect(char **arguments, int index)
{
	int	i;

	if (index == 0)
		return (0);
	i = ft_strlen(arguments[index - 1]);
	i--;
	if (arguments[index - 1][i] == '>' || arguments[index - 1][i] == '<')
		return (1);
	return (0);
}

int	has_command(char **arguments, int index)
{
	int	i;

	i = 0;
	while (arguments[index][i] != '\0')
	{
		if ((arguments[index][i] == '<' || arguments[index][i] == '>')
			&& !is_quoted(arguments[index], i))
			break ;
		i++;
	}
	if (i == 0)
		return (0);
	else
		return (1);
}

char	*take_command(char *input)
{
	int		i;
	char	*command;

	i = 0;
	command = 0;
	while (input[i] != '\0')
	{
		if ((input[i] == '<' || input[i] == '>') && !is_quoted(input, i))
			break ;
		i++;
	}
	if (input[i] == '\0')
		command = ft_strdup(input);
	else
		command = ft_substr(input, 0, i);
	return (command);
}
