/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:02:00 by beaudibe          #+#    #+#             */
/*   Updated: 2023/03/24 21:02:00 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	handle_ctrl_c(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	if (g_global.is_cat == 0)
		rl_redisplay();
	g_global.is_cat = 0;
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