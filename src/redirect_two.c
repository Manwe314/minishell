/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:47:46 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/15 21:48:14 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sub_redirect_one(char *input, int i, int j, char *name)
{
	g_global.last_in = -1;
	name = get_fname_delim(input, i);
	if (change_fd(input, i, name, j) < 0)
	{
		error_handler("infile", 1);
		free(name);
		return (1);
	}
	if (name != 0)
		free(name);
	return (0);
}

int	sub_redirect_two(char *input, int i, int j, char *name)
{
	name = get_fname_delim(input, i);
	if (change_fd(input, i, name, j) < 0)
	{
		error_handler("outfile", 1);
		free(name);
		return (1);
	}
	if (name != 0)
		free(name);
	g_global.last_out = j;
	return (0);
}

int	sub_redirect_three(char *input, int i, int j, char *name)
{
	name = get_fname_delim(input, i);
	if (change_fd(input, i, name, j) < 0)
	{
		error_handler("outfile", 1);
		free(name);
		return (1);
	}
	if (name != 0)
		free(name);
	g_global.last_out = j;
	return (0);
}

int	sub_redirect_four(char *input, int i, int j, char *name)
{
	if (input[i + 1] == '>')
	{
		i++;
		if (sub_redirect_two(input, i, j, name))
			return (-1);
	}
	else if (sub_redirect_three(input, i, j, name))
		return (-1);
	return (i);
}

void	redirect(char *input, int i, int j, char *name)
{
	while (input[i] != '\0')
	{
		if (input[i] == '<' && !is_quoted(input, i))
		{
			if (input[i + 1] == '<')
			{
				g_global.last_in = 1;
				i++;
			}
			else if (sub_redirect_one(input, i, ++j, name))
				return ;
		}
		if (input[i] == '>' && !is_quoted(input, i))
		{
			i = sub_redirect_four(input, i, ++j, name);
			if (i == -1)
				return ;
		}
		if (input[i] != '\0')
			i++;
	}
}