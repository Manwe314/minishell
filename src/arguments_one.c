/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:51:52 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/15 21:53:10 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_new_arguments_size(char **arguments)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (arguments[i] != 0)
	{
		if (i != 0 && is_after_redirect(arguments, i))
			i++;
		if (arguments[i] == 0)
			break ;
		if (has_command(arguments, i))
			size++;
		i++;
	}
	return (size);
}

char **make_new_arguments(char **old, int size)
{
	int i;
	int j;
	char **new;

	i = 0;
	j = 0;
	new = (char **)malloc(sizeof(char *) * (size + 1));
	while (old[i] != 0)
	{
		if (i != 0 && is_after_redirect(old, i))
			i++;
		if (old[i] == 0)
			break ;
		if (has_command(old, i))
		{
			new[j] = take_command(old[i]);
			j++;
		}
		i++;
	}
	new[j] = 0;
	return (new);
}

char **remove_redirections(char **arguments)
{
	int size;
	char **new_arguments;

	size = get_new_arguments_size(arguments);
	new_arguments = make_new_arguments(arguments, size);
	return (new_arguments);
}

void remove_quotes_from_args(char **arguments)
{
	int i;
	int *q_pair;
	char *temp;

	i = 0;
	temp = 0;
	while (arguments[i] != 0)
	{
		q_pair = find_quote_pairs(arguments[i], 0);
		if (q_pair[1] != 0)
		{
			temp = clean_redirection_token(arguments[i], \
			0, ft_strlengnl(arguments[i]));
			free(arguments[i]);
			arguments[i] = temp;
		}
		else
			arguments[i] = handle_dollar(arguments[i]);
		i++;
	}
}

char **clean_up_split(char **arguments)
{
	char **new_arguments;

	new_arguments = remove_redirections(arguments);
	remove_quotes_from_args(new_arguments);
	free_split(arguments);
	return (new_arguments);
}