/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:48:26 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/24 00:37:35 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

int	main(int argc, char *argv[])
{
	char	*input;

	(void)argc;
	(void)argv;
	ft_init_global();
	handle_signals();
	while (1)
	{
		g_global.is_cat = 0;

		input = get_input();
		if (input == NULL)
			break ;
		g_global.is_cat = 0;
		g_global.is_heredoc = 0;
		g_global.command = NULL;
		g_global.pid = getpid();
		g_global.ctrl_c = 0;
		g_global.is_piped = 0;
		g_global.command = input;
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

/*
signals in heredoc
signals ( \ ) exit code
exit code of ctrl \ is 131;
muting siganl apperances with termios
heredoc name varibale never changes <- done
pwd dosent work when in a directory and rm
	-rf ../directory shouyld still print after pwd we get error msg <- done
if unset PATH it segfaults.  <- done
if env  is not included it segfaults <- done

*/
