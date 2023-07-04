/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:02:00 by beaudibe          #+#    #+#             */
/*   Updated: 2023/07/04 19:45:42 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	handle_ctrl_c(int sig)
{
	(void)sig;
	if (g_global.stop_signal)
		return ;
	g_global.exit_status = 1;
	if (g_global.pid == getpid())
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr_fd("\n", 1);
		if (g_global.h_pid > 0)
		{
			g_global.c_happen = 1;
			kill(g_global.h_pid, SIGTERM);
			return ;
		}
		if (g_global.is_waiting == 1)
			return ;
		if ((rl_line_buffer[0] == '\0' || !rl_line_buffer)
			&& g_global.is_cat == 0 && g_global.is_piped == 0)
			rl_redisplay();
		else if (g_global.is_cat == 0 && g_global.is_piped == 1)
			write(1, rl_line_buffer, rl_end);
	}
}

void	handle_ctrl_backslash(int sig)
{
	(void)sig;
	if ((g_global.pid != getpid() && g_global.h_pid > 0)
		|| g_global.stop_signal)
		return ;
	if (g_global.h_pid > 0)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		return ;
	}
	g_global.exit_status = 131;
	if (g_global.is_waiting == 1 && g_global.hdoc == 0)
	{
		ft_putstr_fd("^\\Quit: 3\n", 1);
		return ;
	}
	if (g_global.no_env == 0)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_signals(void)
{
	input_handler(ft_strdup("/bin/stty -echoctl"));
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, handle_ctrl_backslash);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
}
