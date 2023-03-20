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
* ft_cd: change the current working directory to the one specified in path
* will check if the path exists and if the user has the right to access it
* @param: path: the path to the new working directory
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
* ft_echo: print the string str to the standard output
* if n_flag is not 1, it will print a newline at the end of the string
* @param: str: the string to print
*/
int ft_echo(char *str, int n_flag)
{
	ft_putstr_fd(str, 1);
	if (n_flag != 1)
		ft_putstr_fd("\n", 1);
	return (SUCCEED);
}


/*
* ft_pwd: print the current working directory to the standard output
*/
int ft_pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_putstr_fd(\
		"pwd: Error while getting the current working directory\n", 2);
		return (ERROR);
	}
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free(pwd);
	return (SUCCEED);
}

/*
* ft_env: print the environment variables to the standard output
*/
int ft_env(void)
{
	int	i;

	i = -1;
	while (g_global.environ[++i] != NULL)
	{
		ft_putstr_fd(g_global.environ[i], 1);
		ft_putstr_fd("\n", 1);
	}
	return (SUCCEED);
}
