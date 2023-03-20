/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:45:16 by lkukhale          #+#    #+#             */
/*   Updated: 2023/03/20 19:45:49 by lkukhale         ###   ########.fr       */
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
	pid_t executable_to_be_done;

	executable_to_be_done = fork();
	if (executable_to_be_done == 0)
		execve(command, arguments, envp);
	waitpid(executable_to_be_done, NULL, 0);
}
