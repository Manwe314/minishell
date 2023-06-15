/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:13:30 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/15 21:54:40 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *handle_exit_status(void)
{
	int status;
	char *value;

	status = g_global.exit_status;
	if (status >= 0 && status <= 255)
		value = ft_itoa(status);
	else
	{
		status = status % 256;
		value = ft_itoa(status);
	}
	return (value);
}

int handle_exit(char **arguments)
{
	if (split_size(arguments) > 2)
	{
		printf("exit: invalid number of arguments\n");
		return (1);
	}
	else if (arguments[1] != 0 && (check_char(arguments[1]) \
	|| check_bounds(arguments[1])))
	{
		printf("exit: %s: numeric value required\n", arguments[1]);
		g_global.error_status = 2;
		return (255);
	}
	else if (arguments[1] == 0)
	{
		g_global.error_status = 2;
		return (0);
	}
	else
	{
		g_global.error_status = 2;
		return (ft_atoi(arguments[1]) % 256);
	}
}

