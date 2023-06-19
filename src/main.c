/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:48:26 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/19 22:56:49 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global g_global;

int	main(int argc, char *argv[])
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
pwd dosent work when in a directory and rm -rf ../directory shouyld still print after pwd we get error msg <- done
if unset PATH it segfaults.  <- done
if env  is not included it segfaults <- done

*/