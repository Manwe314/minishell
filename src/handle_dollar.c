/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 22:00:08 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/15 22:00:30 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_dollar(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	variable_name_size(char *input, int i)
{
	int	size;

	size = 0;
	while (input[i] != ' ' && input[i] != '\0' && input[i] != 34 &&
			input[i] != 39 && input[i] != '|' && input[i] != '<'
				&& input[i] != '/')
	{
		size++;
		i++;
	}
	return (size);
}

char	*get_variable_value(char *name)
{
	int	len;
	int	i;

	len = ft_strlengnl(name);
	if (len == 0)
		return (ft_strdup("$"));
	if (len == 1 && name[0] == '?')
		return (ft_itoa(g_global.exit_status));
	i = 0;
	while (g_global.environ[i] != 0)
	{
		if (ft_strncmp(name, g_global.environ[i], len) == 0
			&& g_global.environ[i][len] == '=')
			return (ft_strdup(g_global.environ[i] + (len + 1)));
		i++;
	}
	return (ft_strdup(""));
}

char	*expand_variable(char *input, int i, int varibale_size)
{
	char	*name;
	char	*value;

	name = ft_substr(input, ++i, --varibale_size);
	if (ft_strncmp(name, "?", 1) == 0 && ft_strlen(name) == 1)
	{
		value = handle_exit_status();
		free(name);
		return (value);
	}
	value = get_variable_value(name);
	free(name);
	return (value);
}

char	*handle_dollar(char *input)
{
	char *new_input;
	int i;
	int j;

	if (!has_dollar(input))
		return (input);
	i = 0;
	new_input = 0;
	while (input[i] != '\0')
	{
		j = i;
		while (input[j] != '$' && input[j] != '\0')
			j++;
		new_input = ft_strjoingnl(new_input, ft_substr(input, i, j - i));
		i = j;
		if (input[j] == '$')
		{
			i = i + variable_name_size(input, j);
			new_input = ft_strjoingnl(new_input,
										expand_variable(input, j,
												variable_name_size(input, j)));
		}
	}
	free(input);
	return (new_input);
}