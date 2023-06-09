/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:31:55 by marvin            #+#    #+#             */
/*   Updated: 2023/06/16 15:00:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_c(int sig)
{
	(void)sig;
	//ft_putstr_fd("\nminishell$ ", 1);
	rl_replace_line("", 0);
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	if (g_global.is_cat == 0)
		rl_redisplay();
	g_global.is_cat = 0;
	//g_global.ctrl_c = 1;
	//g_global.input = 0;
	//fflush(stdin);
	//fflush(stdout);
}

void	handle_ctrl_d(int sig)
{
	(void)sig;
	ft_putstr_fd("\nExit\n", 1);
	exit(SUCCEED);
}

void	handle_ctrl_backslash(int sig)
{
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	handle_signals(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGTERM, handle_ctrl_d);
	signal(SIGQUIT, handle_ctrl_backslash);
	//signal(SIGTERM, handle_ctrl_backslash);
	// signal(SIGINT, handle_ctrl_backslash);
	// signal(SIGABRT, handle_ctrl_backslash);
	// signal(SIGFPE, handle_ctrl_backslash);
	// signal(SIGILL, handle_ctrl_backslash);
}
