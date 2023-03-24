/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:45:16 by lkukhale          #+#    #+#             */
/*   Updated: 2023/03/22 19:42:05 by lkukhale         ###   ########.fr       */
/*                                                                            */
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

void execute_command(char *command, char **arguments, char **envp)
{
	pid_t	executable_to_be_done;
	int		execve_return;

	//printf("%s\n", command);
	//int i = 0;
	/*while (arguments[i])
	{
		printf("%s\n", arguments[i]);
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
