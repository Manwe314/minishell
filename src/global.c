/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:34:22 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/28 15:52:48 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_global_two(void)
{
	g_global.last_in = 0;
	g_global.fd_size = 0;
	g_global.is_piped = 0;
	g_global.error_status = 0;
	g_global.exit_status = 0;
}

void	ft_init_global_2(void)
{
	g_global.f_pipes[0] = -1;
	g_global.f_pipes[1] = -1;
	g_global.last_out = -1;
	g_global.is_cat = 0;
	g_global.pid = getpid();
	g_global.h_pid = -1;
	g_global.ctrl_c = 0;
}

void	ft_init_global(void)
{
	int			i;
	extern char	**environ;

	i = 0;
	while (environ[i])
		i++;
	g_global.no_env = 0;
	if (i == 0)
		g_global.no_env = 1;
	g_global.environ = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (environ[++i])
	{
		g_global.environ[i] = ft_strdup(environ[i]);
	}
	g_global.history = malloc(sizeof(char *) * 1);
	g_global.history[0] = NULL;
	g_global.environ[i] = NULL;
	g_global.fds = 0;
	g_global.save_stdin = dup(STDIN_FILENO);
	g_global.save_stdout = dup(STDOUT_FILENO);
	g_global.here_doc = 0;
	g_global.last_write_pipe = -1;
	ft_init_global_2();
}

void	ft_free_global(void)
{
	int	i;

	i = -1;
	while (g_global.environ[++i])
	{
		free(g_global.environ[i]);
	}
	free(g_global.environ);
}
