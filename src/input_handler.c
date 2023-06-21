/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:54:42 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/21 21:30:49 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(void)
{
	char	*input;

	input = readline("minishell$ ");
	if (input == NULL)
		return (NULL);
	return (input);
}

int	input_handler(char *input)
{
	char **arguments;
	char *command;

	if (!validate_input(input))
		return (error_handler("invalid input", 0));
	if (check_piping(input))
	{
		input = set_up_piping(input);
		if (input != 0)
			piping(input);
		clean_up(0, 0, input);
		return (0);
	}
	do_redirections(input);
	if (g_global.error_status == 0 && g_global.ctrl_c != 1)
	{
		arguments = ft_split_q(input, ' ');
		arguments = clean_up_split(arguments);
		command = get_clean_command(arguments);
		execution(command, arguments);
		clean_up(arguments, command, input);
	}
	else
		clean_up(0, 0, input);
	return (0);
}