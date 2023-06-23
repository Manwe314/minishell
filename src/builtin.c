/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hall <hall@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:45:00 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/23 22:14:50 by hall             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_buitin(char **str)
{
	if (ft_strncmp(str[0], "echo", 4) == 0)
		return (SUCCEED);
	else if (ft_strncmp(str[0], "cd\0", 3) == 0)
		return (SUCCEED);
	else if (ft_strncmp(str[0], "pwd\0", 4) == 0)
		return (SUCCEED);
	else if (ft_strncmp(str[0], "export\0", 7) == 0)
		return (SUCCEED);
	else if (ft_strncmp(str[0], "unset\0", 6) == 0)
		return (SUCCEED);
	else if (ft_strncmp(str[0], "env\0", 4) == 0)
		return (SUCCEED);
	else if (ft_strncmp(str[0], "history\0", 8) == 0)
		return (SUCCEED);
	else if (ft_strncmp(str[0], "exit\0", 5) == 0)
		return (SUCCEED);
	return (ERROR);
}

int	ft_execute_command_builtin(char **str)
{
	if (ft_strncmp(str[0], "echo", 4) == 0)
		return (ft_echo(str));
	else if (ft_strncmp(str[0], "cd", 2) == 0)
		return (ft_cd(str));
	else if (ft_strncmp(str[0], "pwd", 3) == 0)
		return (ft_pwd());
	else if (ft_strncmp(str[0], "export", 6) == 0)
		return (ft_export_str(str));
	else if (ft_strncmp(str[0], "unset", 5) == 0)
		return (ft_unset_str(str));
	else if (ft_strncmp(str[0], "env", 3) == 0)
		return (ft_env());
	else if (ft_strncmp(str[0], "history", 7) == 0)
	{
		ft_history();
		return (0);
	}
	else if (ft_strncmp(str[0], "exit\0", 5) == 0)
		return (handle_exit(str));
	return (-1);
}
