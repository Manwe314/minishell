/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:45:01 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/24 01:12:20 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sub_clean_up_one(char **arguments, char *command, char *input)
{
	if (arguments != 0)
		free_split(arguments);
	if (command != 0)
		free(command);
	if (input != 0)
		free(input);
}

void	sub_clean_up_two(void)
{
	if (g_global.fds != 0)
	{
		free(g_global.fds);
		g_global.fds = 0;
	}
}

void	clean_up(char **arguments, char *command, char *input)
{
	int	i;

	i = 0;
	sub_clean_up_one(arguments, command, input);
	while (i < g_global.fd_size)
	{
		close(g_global.fds[i]);
		i++;
	}
	g_global.fd_size = 0;
	if (dup2(g_global.save_stdin, STDIN_FILENO) < 0)
		error_handler("dup2 clean", 2);
	if (dup2(g_global.save_stdout, STDOUT_FILENO) < 0)
		error_handler("dup2 clean", 2);
	g_global.is_piped = 0;
	if (g_global.here_doc != 0)
	{
		free(g_global.here_doc);
		g_global.here_doc = 0;
	}
	g_global.last_in = 0;
	g_global.last_out = -1;
	g_global.ctrl_c = 0;
	g_global.h_pid = -1;
}
