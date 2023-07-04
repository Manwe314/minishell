/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:43:09 by lkukhale          #+#    #+#             */
/*   Updated: 2023/07/04 19:57:48 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_hdoc_in(int id)
{
	t_doc	*temp;

	temp = g_global.docs;
	while (temp != 0)
	{
		if (temp->num == id)
		{
			if (temp->doc != 0)
				g_global.here_doc = ft_strdup(temp->doc);
		}
		temp = temp->next;
	}
}

void	handle_pipd_hdoc(char **split)
{
	int		i;
	t_doc	*temp;

	g_global.docs = (t_doc *)malloc(sizeof(t_doc));
	i = 0;
	temp = g_global.docs;
	while (split[i] != 0)
	{
		temp->num = i;
		do_heredocs(split[i]);
		if (g_global.here_doc != 0)
			temp->doc = ft_strdup(g_global.here_doc);
		else
			temp->doc = 0;
		if (split[i + 1] == 0)
			temp->next = 0;
		else
			temp->next = (t_doc *)malloc(sizeof(t_doc));
		if (g_global.c_happen == 1)
		{
			temp->next = 0;
			g_global.error_status = 1;
			break ;
		}
		temp = temp->next;
		i++;
	}
}

void	piped_command_start(char *input, int *pip, int i)
{
	put_hdoc_in(i);
	if (dup2(pip[1], STDOUT_FILENO) < 0)
		error_handler("dup PcS:", 1);
	g_global.last_write_pipe = dup(pip[1]);
	close(pip[0]);
	close(pip[1]);
	input_handler(input);
	exit(g_global.exit_status);
}

void	piped_command_end(char *input, int *pip, int i)
{
	put_hdoc_in(i);
	if (dup2(pip[0], STDIN_FILENO) < 0)
		error_handler("dup PcE:", 1);
	close(pip[1]);
	close(pip[0]);
	input_handler(input);
	exit(g_global.exit_status);
}

void	piped_command_middle(char *input, int *inpip, int *outpip, int i)
{
	put_hdoc_in(i);
	if (dup2(inpip[0], STDIN_FILENO) < 0)
		error_handler("dup PcM-i:", 1);
	if (dup2(outpip[1], STDOUT_FILENO) < 0)
		error_handler("dup PcM-o:", 1);
	g_global.last_write_pipe = dup(outpip[1]);
	close(outpip[0]);
	close(inpip[0]);
	close(inpip[1]);
	close(outpip[1]);
	input_handler(input);
	exit(g_global.exit_status);
}

void	piping(char *input)
{
	int		size;
	char	**pipe_split;

	pipe_split = ft_split_q(input, '|');
	size = split_size(pipe_split);
	g_global.is_piped = 1;
	handle_pipd_hdoc(pipe_split);
	if (g_global.error_status == 0)
		pipeline(pipe_split, size);
	free_split(pipe_split);
}

char	*set_up_piping(char *input)
{
	char	*temp;

	if (initial_pipe_check(input) == 1)
	{
		temp = finish_piped_input(input);
		if (!validate_input(temp))
		{
			free(temp);
			return (0);
		}
		else
			return (temp);
	}
	else
		return (input);
}
