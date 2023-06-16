/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:35:41 by marvin            #+#    #+#             */
/*   Updated: 2023/06/16 14:53:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_size(char **split)
{
	int	i;

	i = 0;
	while (split[i] != 0)
		i++;
	return (i);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != 0)
	{
		free(split[i]);
		i++;
	}
	free(split[i]);
	free(split);
}

int	is_begining(char *input, int index)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (i >= index && input[index] == ' ')
		return (1);
	return (0);
}

int	*find_quote_pairs(char *input, int start)
{
	int			i;
	int			j;
	static int	quote_pair[2];

	i = start;
	quote_pair[0] = 0;
	quote_pair[1] = 0;
	while (input[i] != '\0')
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
		i++;
	}
	return (quote_pair);
}

void execute_command(char *command, char **arguments, char **envp)
{
	pid_t	executable_to_be_done;
	int		execve_return;

	/*printf("Command: %s\n", command);
	int i = 0;
	while (arguments[i])
	{
		printf("Argument[%d]: %s\n", i, arguments[i]);
		i++;
	}*/
	if (g_global.last_write_pipe != -1)
	{
		//ft_putstr_fd("1\n", g_global.save_STDOUT);
		close(g_global.last_write_pipe);
	}
	execve_return = 1;
	executable_to_be_done = fork();
	if (executable_to_be_done == 0){
		execve_return = execve(command, arguments, envp);
	}
	if (execve_return == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	waitpid(executable_to_be_done, NULL, 0);
}

void	change_quoted_char(char *input)
{
	int	i;

	if (g_global.quoted_flags == 0)
		return ;
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '<' && is_flaged(i))
			input[i] = '&';
		if (input[i] == '>' && is_flaged(i))
			input[i] = '*';
		if (input[i] == '|' && is_flaged(i))
			input[i] = ';';
		if (input[i] == 34 && is_flaged(i))
			input[i] = '(';
		if (input[i] == 39 && is_flaged(i))
			input[i] = ')';
		if (input[i] == '$' && is_flaged(i))
			input[i] = '!';
		i++;
	}
	free(g_global.quoted_flags);
	g_global.quoted_flags = 0;
}
