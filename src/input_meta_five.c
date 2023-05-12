/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_meta_five.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:39:33 by lkukhale          #+#    #+#             */
/*   Updated: 2023/05/12 15:41:59 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_all_space(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		if (input[i] == ' ' || input[i] == '	')
			j++;
		i++;
	}
	if (i == j)
		return (1);
	return (0);
}

void	pipeline(char **input, int size)
{
	pid_t	*pids;
	int	i;
	int	**pipes;

	pids = (pid_t *)malloc(sizeof(pid_t) * size);
	pipes = (int **)malloc(sizeof(int *) * (size - 1));
	i = 0;
	while (input[i] != 0)
	{
		if (i < size - 1)
		{
			pipes[i] = (int *)malloc(sizeof(int) * 2);
			if (pipe(pipes[i]) < 0)
				perror("Pipe"); // error handler maybe?
		}
		pids[i] = fork();
		if (pids[i] < 0)
			perror("Fork"); // error handler maybe?
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
	i = 0;
	while (i < size)
	{
		waitpid(pids[i], NULL, 0);
		//printf("outed[%d]: %d\n", i , pids[i]);
		i++;
	}
	i = 0;
	while (i < size - 1)
	{
		close(pipes[i][0]);
		free(pipes[i]);
		i++;
	}
	g_global.last_write_pipe = -1;
	dup2(g_global.save_STDIN, STDIN_FILENO);
	dup2(g_global.save_STDOUT, STDOUT_FILENO);
	free(pids);
	free(pipes);
}

void	execute_case_four(char *input)
{
	char **new_input;
	int	i;
	int	size;

	i = initial_pipe_check(input);
	if (i == -1)
	{
		perror("Invalid Token"); // need actual error msger
		free(input);
		return ;
	}
	if (i == 1)
		input = finish_piped_input(input);
	new_input = ft_split(input, '|');
	i = 0;
	size = split_size(new_input);
	while (new_input[i] != 0)
	{
		if (is_all_space(new_input[i]))
		{
			perror("Syntax error"); // best have error mesinger
			break;
		}
		i++;
	}
	if (i != size && i + 1 != size)
		return ;
	pipeline(new_input, size);
}