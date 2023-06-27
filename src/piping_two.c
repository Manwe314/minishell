/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:44:04 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/27 21:17:17 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*finish_piped_input(char *input)
{
	char	*added_input;

	while (1)
	{
		added_input = readline("> ");
		if (is_all_space(added_input) == 0)
		{
			if (initial_pipe_check(added_input) != 1)
				break ;
		}
		input = ft_strjoingnl(input, added_input);
	}
	if (added_input != 0)
		input = ft_strjoingnl(input, added_input);
	return (input);
}

void	sub_pipeline_one(char **input, pid_t *pids, int **pipes, int size)
{
	int	i;

	i = 0;
	while (input[i] != 0)
	{
		if (i < size - 1)
		{
			pipes[i] = (int *)malloc(sizeof(int) * 2);
			if (pipe(pipes[i]) < 0)
				error_handler("Pipe", 1);
		}
		do_heredocs(input[i]);
		pids[i] = fork();
		if (pids[i] < 0)
			error_handler("Fork", 1);
		if (i == 0 && pids[i] == 0)
			piped_command_start(input[i], pipes[0]);
		if (i != 0 && i != size - 1 && pids[i] == 0)
			piped_command_middle(input[i], pipes[i - 1], pipes[i]);
		if (i == size - 1 && pids[i] == 0)
			piped_command_end(input[i], pipes[size - 2]);
		if (i < size - 1)
			close(pipes[i][1]);
		i++;
	}
}

void	sub_pipeline_two(int size, int **pipes)
{
	int	i;

	i = 0;
	while (i < size - 1)
	{
		close(pipes[i][0]);
		free(pipes[i]);
		i++;
	}
}

void	pipeline(char **input, int size)
{
	pid_t	*pids;
	int		i;
	int		**pipes;
	int		status;

	pids = (pid_t *)malloc(sizeof(pid_t) * size);
	pipes = (int **)malloc(sizeof(int *) * (size - 1));
	sub_pipeline_one(input, pids, pipes, size);
	sub_pipeline_two(size, pipes);
	i = 0;
	while (i < size)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		g_global.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_global.exit_status = WTERMSIG(status);
	else
		g_global.exit_status = EXIT_FAILURE;
	g_global.last_write_pipe = -1;
	free(pids);
	free(pipes);
}
