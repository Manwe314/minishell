/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/05/04 20:58:08 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "minishell.h"

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
	int i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (i >= index && input[index] == ' ')
		return (1);
	return (0);

}

int	*find_quote_pairs(char *input, int start)
{
	int	i;
	int j;
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
	execve_return = 1;
	executable_to_be_done = fork();
	if (executable_to_be_done == 0)
		execve_return = execve(command, arguments, envp);
	if (execve_return == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	waitpid(executable_to_be_done, NULL, 0);
}
