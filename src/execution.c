/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 22:00:52 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/19 17:23:30 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sub_execute_cmd_one(void)
{
	if (g_global.last_write_pipe != -1)
	{
		if (dup2(g_global.last_write_pipe, STDOUT_FILENO) < 0)
			perror("dup2 excve:");
		close(g_global.last_write_pipe);
	}
}

int execute_command(char *command, char **arguments, char **envp)
{
	pid_t	executable_to_be_done;
	int		execve_return;
	int		status;

	if (ft_strncmp(arguments[0], "cat\0", 4) == 0)
		g_global.is_cat = 1;
	sub_execute_cmd_one();
	execve_return = 1;
	executable_to_be_done = fork();
	if (executable_to_be_done == 0)
		execve_return = execve(command, arguments, envp);
	if (execve_return == -1)
	{
		perror(command);
		exit(EXIT_FAILURE);
	}
	waitpid(executable_to_be_done, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	else
		return(EXIT_FAILURE);
}

void	execution(char *command, char **arguments)
{
	if (ft_is_buitin(arguments))
		g_global.exit_status = ft_execute_command_builtin(arguments);
	else if (command != 0)
		g_global.exit_status = execute_command(command, arguments, g_global.environ);
}