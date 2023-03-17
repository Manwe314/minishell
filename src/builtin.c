/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:16:07 by beaudibe          #+#    #+#             */
/*   Updated: 2023/03/17 13:16:07 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
// ft_cd: change the current working directory to the one specified in path
// will check if the path exists and if the user has the right to access it
// @param: path: the path to the new working directory
*/
int ft_cd(char *path)
{
	if (access(path, F_OK) != -1)
	{
		if (chdir(path) == -1)
		{
			ft_putstr_fd("cd: Error while changing repertories", 2);
			return (ERROR);
		}
	}
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory", 2);
		return (ERROR);
	}
	return (SUCCEED);
}


/*
// ft_echo: print the string str to the standard output
// if n_flag is set to 1, a # will be printed at the end of the string
// if it doesn't end with a newline
// @param: str: the string to print
*/
int ft_echo(char *str, int n_flag)
{
	ft_putstr_fd(str, 1);
	if (n_flag == 1 && str[ft_strlen(str) - 1] != '\n')
		ft_putstr_fd("#", 1);
	ft_putstr_fd("\n", 1);
	return (SUCCEED);
}



