/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:45:01 by lkukhale          #+#    #+#             */
/*   Updated: 2023/07/04 20:15:57 by lkukhale         ###   ########.fr       */
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
	g_global.last_in = 0;
	if (g_global.error_status != 2)
		g_global.error_status = 0;
	g_global.last_out = -1;
	g_global.h_pid = -1;
	g_global.is_piped = 0;
	g_global.c_happen = 0;
}

void	sub_clean_up_three(char *input)
{
	t_doc	*temp;

	temp = g_global.docs;
	if (check_piping(input) != 1)
		free(g_global.fds);
	if (g_global.here_doc != 0)
	{
		free(g_global.here_doc);
		g_global.here_doc = 0;
	}
	while (g_global.docs != 0)
	{
		temp = g_global.docs->next;
		free(g_global.docs->doc);
		free(g_global.docs);
		g_global.docs = temp;
	}
}

void	clean_up(char **arguments, char *command, char *input)
{
	int	i;

	i = 0;
	sub_clean_up_three(input);
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
	sub_clean_up_two();
}
