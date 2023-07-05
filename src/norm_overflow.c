/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_overflow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:34:33 by lkukhale          #+#    #+#             */
/*   Updated: 2023/07/05 16:46:15 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd_er(void)
{
	int		i;
	char	*temp;

	i = find_pwd();
	ft_putstr_fd("cd: error retrieving current directory: ", \
	g_global.save_stdout);
	perror("getcwd");
	if (i < 0)
		return ;
	temp = ft_strjoin(g_global.environ[i], "/..");
	free(g_global.environ[i]);
	g_global.environ[i] = temp;
}

void	do_pipd_heredoc(char *input)
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

char	*sub_handle_pipd_hdoc(void)
{
	char	*temp;

	if (g_global.here_doc != 0)
		temp = ft_strdup(g_global.here_doc);
	else
		temp = 0;
	return (temp);
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
		temp->doc = sub_handle_pipd_hdoc();
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
