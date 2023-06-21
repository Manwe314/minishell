/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:02:00 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/21 21:44:01 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_c(int sig)
{
	(void)sig;
	g_global.ctrl_c = 1;
	if (g_global.h_pid > 0)
	{
		kill(g_global.h_pid, SIGTERM);
	}
	else if (g_global.is_cat == 0)
		rl_redisplay();
	if (g_global.pid == getpid())
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr_fd("\n", 1);
	}
}

void	handle_ctrl_d(int sig)
{
	(void)sig;
	if (g_global.hdoc != 1)
	{
		ft_putstr_fd("\nExit\n", 1);
	}
	exit(SUCCEED);
}

void	handle_ctrl_backslash(int sig)
{
	rl_on_new_line();
	rl_redisplay();
	g_global.exit_status = 131;
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