/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2023/03/24 21:02:00 by beaudibe          #+#    #+#             */
/*   Updated: 2023/03/24 21:02:00 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"


// !There's still some thing written when you do ctrl + c when you have start a
// !command.
// ? Maybe we should use a global variable in the readline function
void	handle_ctrl_c(int sig)
{
	(void)sig;
	ft_putstr_fd("\nminishell$ ", 1);
}

void	handle_ctrl_d(int sig)
{
	(void)sig;
	ft_putstr_fd("\nExit\n", 1);
	exit(SUCCEED);
}

void	handle_ctrl_backslash(int sig)
{
	(void)sig;
}

void	handle_signals(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGTERM, handle_ctrl_d);
	signal(SIGQUIT, handle_ctrl_backslash);
	signal(SIGTERM, handle_ctrl_backslash);
}
