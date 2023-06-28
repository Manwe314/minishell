/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_five.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:08:07 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/28 16:15:30 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_variable_name(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0' && input[i] != '=')
		i++;
	return (ft_substr(input, 0, i));
}

char	**refactor_arguments(char **arguments)
{
	int		size;
	int		i;
	char	**new_arguments;

	i = -1;
	size = 0;
	while (arguments[++i] != 0)
	{
		if (arguments[i][0] != ' ')
			size++;
	}
	new_arguments = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	size = 0;
	while (arguments[i] != 0)
	{
		if (arguments[i][0] != ' ')
		{
			new_arguments[size] = ft_strdup(arguments[i]);
			size++;
		}
		i++;
	}
	new_arguments[size] = 0;
	return (new_arguments);
}

void	sub_remove_duplicates(char **arguments, char *name, int i)
{
	char	*temp;
	int		j;

	j = i + 1;
	while (arguments[j] != 0)
	{
		temp = get_variable_name(arguments[j]);
		if (ft_strncmp(name, temp, ft_strlen(name)) == 0 \
		&& ft_strlen(name) == ft_strlen(temp))
		{
			free(arguments[i]);
			arguments[i] = ft_strdup(" ");
			free(temp);
			break ;
		}
		free(temp);
		j++;
	}
}

char	**remove_duplicates(char **arguments)
{
	int		i;
	char	*name;

	i = 1;
	while (arguments[i] != 0)
	{
		name = get_variable_name(arguments[i]);
		sub_remove_duplicates(arguments, name, i);
		free(name);
		i++;
	}
	return (refactor_arguments(arguments));
}
