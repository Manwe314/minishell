/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:34:22 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/16 15:54:09 by marvin           ###   ########.fr       */
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

void	ft_init_global(void)
{
	int			i;
	extern char	**environ;

	i = 0;
	while (environ[i])
		i++;
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
	g_global.save_STDIN = dup(STDIN_FILENO);
	g_global.save_STDOUT = dup(STDOUT_FILENO);
	g_global.here_doc = 0;
	g_global.last_write_pipe = -1;
	g_global.f_pipes[0] = -1;
	g_global.f_pipes[1] = -1;
	g_global.last_out = -1;
	g_global.is_cat = 0;
}

char	*ft_remove_n(char *str)
{
	if (str[ft_strlen(str) - 1] == '\n')
		str[ft_strlen(str) - 1] = '\0';
	return (str);
}

void	ft_free_global(void)
{
	int i;

	i = -1;
	while (g_global.environ[++i])
	{
		free(g_global.environ[i]);
	}
	free(g_global.environ);
}