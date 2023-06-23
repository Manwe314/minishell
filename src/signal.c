/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:02:00 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/24 00:01:49 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_c(int sig)
{
	(void)sig;
	g_global.ctrl_c = 1;
	g_global.exit_status = 130;
	if (g_global.pid == getpid())
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		if (g_global.hdoc == 1)
		{
			rl_redisplay();
			g_global.hdoc = 0;
			return ;
		}
		if ((rl_line_buffer[0] == '\0' || !rl_line_buffer) && g_global.is_cat == 0 && g_global.is_piped == 0)
			rl_redisplay();
		else if (g_global.is_cat == 0 && g_global.is_piped == 1)
			write(1, rl_line_buffer, rl_end);
	}
}

void	handle_ctrl_backslash(int sig)
{
	(void)sig;
	g_global.exit_status = 131;
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void	handle_signals(void)
{
	input_handler(ft_strdup("stty -echoctl"));
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, handle_ctrl_backslash);
}
