/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:45:53 by lkukhale          #+#    #+#             */
/*   Updated: 2023/07/04 20:10:38 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sub_handle_heredoc_one(void)
{
	if (g_global.here_doc != 0)
	{
		free(g_global.here_doc);
		g_global.here_doc = 0;
	}
	if (dup2(g_global.save_stdin, STDIN_FILENO) < 0)
		error_handler("here_doc", 2);
	if (dup2(g_global.save_stdout, STDOUT_FILENO) < 0)
		error_handler("here_doc", 2);
}

void	sub_handle_heredoc_two(void)
{
	if (g_global.last_out >= 0)
	{
		if (dup2(g_global.fds[g_global.last_out], STDOUT_FILENO) < 0)
			error_handler("dup2 last out", 1);
		g_global.last_out = -1;
	}
}

void	handle_heredoc(char *delim)
{
	char	*buff;
	int		pip[2];

	sub_handle_heredoc_one();
	pipe(pip);
	g_global.hdoc = 1;
	g_global.h_pid = fork();
	if (g_global.h_pid == 0)
		exit(heredoc(pip[0], pip[1], delim));
	close(pip[1]);
	waitpid(g_global.h_pid, NULL, 0);
	buff = ft_strdup(" ");
	while (read(pip[0], buff, 1) > 0)
	{
		g_global.here_doc = ft_strjoingnl(g_global.here_doc, buff);
		buff = ft_strdup(" ");
	}
	free(buff);
	close(pip[0]);
	g_global.hdoc = 0;
	sub_handle_heredoc_two();
	free(delim);
}

void	do_heredocs(char *input)
{
	int		i;
	char	*delim;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '<' && !is_quoted(input, i))
		{
			if (input[i + 1] == '<')
			{
				delim = get_fname_delim_hdoc(input, i + 1);
				if (delim != 0)
					handle_heredoc(delim);
			}
		}
		i++;
	}
}

void do_pipd_heredoc(char *input)
{
	int	i;

	i = ft_strlen(input);

	while (i >= 0)
	{
		if (input[i] == '<')
		{
			if (i > 0 && input[i - 1] == '<')
			{
				g_global.last_in = 1;
				break ;
			}
			else
			{
				g_global.last_in = -1;
				break ;
			}
		}
		i--;
	}
}

void	do_redirections(char *input)
{
	if (g_global.is_piped == 0)
		do_heredocs(input);
	else
		do_pipd_heredoc(input);
	g_global.fsize = get_fd_size(input);
	g_global.fds = malloc(sizeof(int) * g_global.fsize);
	redirect(input, 0, -1, 0);
	if (g_global.last_in == 1)
	{
		if (pipe(g_global.f_pipes) < 0)
			error_handler("here_doc", 1);
		if (dup2(g_global.f_pipes[0], STDIN_FILENO) < 0)
			error_handler("here_doc dup2", 1);
		ft_putstr_fd(g_global.here_doc, g_global.f_pipes[1]);
		close(g_global.f_pipes[1]);
		g_global.f_pipes[1] = -1;
	}

}
