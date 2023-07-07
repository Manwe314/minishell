/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:48:26 by beaudibe          #+#    #+#             */
/*   Updated: 2023/07/07 15:17:15 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

void	reset_global(char *input)
{
	g_global.is_cat = 0;
	g_global.is_heredoc = 0;
	g_global.command = NULL;
	g_global.pid = getpid();
	g_global.is_piped = 0;
	g_global.command = input;
}

void	reset_global_before(void)
{
	g_global.is_cat = 0;
	g_global.is_waiting = 0;
	g_global.stop_signal = 0;
}

int	main(int argc, char *argv[])
{
	char	*input;

	(void)argc;
	(void)argv;
	ft_init_global();
	handle_signals();
	while (1)
	{
		reset_global_before();
		input = get_input();
		if (input == NULL)
			break ;
		g_global.is_waiting = 1;
		reset_global(input);
		if (ft_strlengnl(input) > 0)
			ft_add_history(input);
		input_handler(input);
		if (g_global.error_status == 2)
			break ;
	}
	ft_putstr_fd("exit\n", 1);
	ft_clear_history();
	ft_free_global();
	return (g_global.exit_status);
}
