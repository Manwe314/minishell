/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:48:26 by beaudibe          #+#    #+#             */
/*   Updated: 2023/05/11 18:24:00 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global g_global;

void ft_init_global()
{
	int i;
	extern char **environ;
	i = 0;
	while (environ[i])
		i++;
	g_global.environ = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (environ[++i]){
		g_global.environ[i] = ft_strdup(environ[i]);
	}
	g_global.history = malloc(sizeof(char *) * 1);
	g_global.history[0] = NULL;
	g_global.environ[i] = NULL;
	g_global.fds = 0;
	g_global.save_STDIN = dup(STDIN_FILENO);
	g_global.save_STDOUT = dup(STDOUT_FILENO);
	g_global.here_doc = 0;
	g_global.f_pipes[0] = -1;
	g_global.f_pipes[1] = -1;
	g_global.last_out = -1;
	g_global.last_in = 0;
	g_global.last_write_pipe = -1;
}

char *ft_remove_n(char *str)
{
	if (str[ft_strlen(str) - 1] == '\n')
		str[ft_strlen(str) - 1] = '\0';
	return (str);
}

void	ft_free_global()
{
	int i;

	i = -1;
	while (g_global.environ[++i])
	{
		free(g_global.environ[i]);
	}
	free(g_global.environ);
}
/*
! remember that on bash, the prompt is $USER@$HOSTNAME:$PWD$
*/

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	char* input;

	ft_init_global();

	handle_signals();
	while(1)
	{
		input = get_input();
		if (input == NULL)
			break ;
		handle_input(input, envp);
		ft_add_history(input);
		//ft_cd(msg);
		//free(msg);
	}
	ft_putstr_fd("exit\n", 1);
	ft_clear_history();
	ft_free_global();
	return (0);
}
