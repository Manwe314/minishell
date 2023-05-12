/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_meta_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:13:45 by lkukhale          #+#    #+#             */
/*   Updated: 2023/05/11 20:17:49 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_up_execution_two(char **arguments)
{
	char	*input;
	char	*temp;
	int	i;
	int j;

	i = 0;
	input = 0;
	j = 0;
	g_global.fds = (int*)malloc(sizeof(int) * get_fd_size(arguments));
	while (arguments[i] != 0)
	{
		//printf("redirect case[%d]: %d\n",i , redirect_case(arguments, i));
		if (redirect_case(arguments, i) == 0)
		{
			temp = ft_strdup(arguments[i]);
			input = ft_strjoingnl(input, temp);
			temp = input;
			input = ft_strjoin(input, " ");
			free(temp);
		}
		if (redirect_case(arguments, i) == 1)
		{
			if (arguments[i + 1] != 0 && arguments[i][0] =='<')
			{
				g_global.fds[j] = open(arguments[i + 1], O_RDONLY);
				if (g_global.fds[j] < 0)
				{
					perror("failed to open a file");// could have a custom error function here;
					return (0);
				}
				dup2(g_global.fds[j], 0);
				g_global.last_in = 1;
				j++;
			}
			if (arguments[i + 1] != 0 && arguments[i][0] =='>')
			{
				g_global.fds[j] = open(arguments[i + 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
				if (g_global.fds[j] < 0)
				{
					perror("failed to create a file");// could have a custom error function here;
					return (0);
				}
				dup2(g_global.fds[j], 1);
				g_global.last_out = j;
				j++;
			}
		}
		if (redirect_case(arguments, i) == 2)
		{
			if (arguments[i + 1] != 0 && arguments[i][0] =='<')
			{
				if (ft_strlen(arguments[i]) > 2)
				{
					perror("Invalid token"); //need real error handler here
					return (0);
				}
				handle_heredoc(ft_strdup(arguments[i + 1]));
				g_global.last_in = -1;

			}
			if (arguments[i + 1] != 0 && arguments[i][0] =='>')
			{
				if (ft_strlen(arguments[i]) > 2)
				{
					perror("Invalid token"); //need real error handler here
					return (0);
				}
				g_global.fds[j] = open(arguments[i + 1], O_APPEND | O_CREAT | O_RDWR, 0644);
				if (g_global.fds[j] < 0)
				{
					perror("failed to create a file");// could have a custom error function here;
					return (0);
				}
				dup2(g_global.fds[j], 1);
				g_global.last_out = j;
				j++;
			}
		}
		i++;
	}
	// if last element of arguments is < > << >> need to send an error;
	return (input);
}

void	close_fds(int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (g_global.fds[i] >= 0)
			close(g_global.fds[i]);
		i++;
	}
	free(g_global.fds);
	g_global.fds = 0;
	if (dup2(g_global.save_STDIN, STDIN_FILENO) < 0)
		perror("close dup2");
	if (dup2(g_global.save_STDOUT, STDOUT_FILENO) < 0)
		perror("close dup2");
	if (g_global.f_pipes[0] >= 0)
	{
		close(g_global.f_pipes[0]);
		g_global.f_pipes[0] = -1;
	}
	if (g_global.f_pipes[1] >= 0)
	{
		close(g_global.f_pipes[1]);
		g_global.f_pipes[1] = -1;
	}
}

void	execute_case_two(char *input)
{
	char	*new_input;
	char	**arguments;
	int		casse;

	new_input = insert_spaces(input);
	free(input);
	arguments = ft_split(new_input, ' ');
	free(new_input);
	new_input = set_up_execution_two(arguments);
	if (g_global.last_in == -1 && new_input != 0)
	{
		if (pipe(g_global.f_pipes) < 0)
			perror("pipes"); // error handlinging
		dup2(g_global.f_pipes[0], STDIN_FILENO);
		ft_putstr_fd(g_global.here_doc, g_global.f_pipes[1]);
		close(g_global.f_pipes[1]);
		g_global.f_pipes[1] = -1;
		if (g_global.last_write_pipe >= 0)
		{
			dup2(g_global.last_write_pipe, STDOUT_FILENO);
			close(g_global.last_write_pipe);
		}
	}
	g_global.last_in = 0;
	g_global.last_out = -1;
	if (new_input != 0)
	{
		casse = detect_path_executable(new_input);
		if (casse > 0)
			do_pathed_executable(new_input, casse, g_global.environ);
		if (casse == 0)
			do_base_case(new_input, g_global.environ);
	}
	close_fds(get_fd_size(arguments));
	free_split(arguments);
}