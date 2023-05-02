/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_builtin.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:13:30 by beaudibe          #+#    #+#             */
/*   Updated: 2023/05/02 18:06:55 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export_str(char **str)
{
	int	i;
	int	j;

	i = 0;
	if (!str[1])
		return (ft_print_env_alphabeticaly());
	while (str[++i])
		j = ft_export(str[i]);
	return (j);
}

int	ft_unset_str(char **str)
{
	int	i;
	int	j;

	i = 0;
	if (!str[1])
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return (ERROR);
	}
	while (str[++i])
		j = ft_unset(str[i]);
	return (j);
}

/*
* ft_is_buitin: check if the command is a builtin
* @str: the command
* @return: 1 if it is, 0 if not
*/
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
	return (ERROR);
}

int	ft_execute_command_builtin(char **str)
{
	if (ft_strncmp(str[0], "echo", 4) == 0)
		return (ft_echo(str, ft_strncmp(str[1], "-n\0", 3) == 0));
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
		return (ft_history());
	return (-1);
}
