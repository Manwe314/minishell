/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:45:53 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/19 23:07:04 by lkukhale         ###   ########.fr       */
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
	if (dup2(g_global.save_STDIN, STDIN_FILENO) < 0)
		error_handler("here_doc", 2);
	if (dup2(g_global.save_STDOUT, STDOUT_FILENO) < 0)
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
	char	*input;
	char	*temp;

	sub_handle_heredoc_one();
	while (1)
	{
		if (g_global.ctrl_c == 1)
			break ;
		input = readline("> ");
		if ((ft_strncmp(delim, input, (unsigned int)ft_strlengnl(delim)) == 0
				&& ft_strlen(delim) == ft_strlen(input)) || input == NULL \
				|| g_global.ctrl_c == 1)
		{
			free(input);
			break ;
		}
		temp = input;
		input = ft_strjoin(input, "\n");
		free(temp);
		g_global.here_doc = ft_strjoingnl(g_global.here_doc, input);
	}
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
			if (input[i + 1] == '<')
			{
				delim = get_fname_delim_hdoc(input, i + 1);
				if (delim != 0)
					handle_heredoc(delim);
			}
		i++;
	}
}

void	do_redirections(char *input)
{
	int size;

	if (g_global.is_piped == 0)
		do_heredocs(input);
	size = get_fd_size(input);
	g_global.fds = malloc(sizeof(int) * size);
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