/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:45:00 by beaudibe          #+#    #+#             */
/*   Updated: 2023/05/09 12:45:00 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int env_exist(char *str)
{
	int	i;

	i = -1;
	while (g_global.environ[++i])
		if (ft_strncmp(g_global.environ[i], str, ft_strlen(str)) == 0)
			return (i);
	return (-1);
}

/*
* ft_cd: change the current working directory to the one specified in path
* will check if the path exists and if the user has the right to access it
* @param: path: the path to the new working directory
*/
int	ft_cd(char **path) //just cd, crashes.
{
	printf("cdio\n");
	char *temp;

	if (path[1] != 0 && path[2] != 0)
	{
		ft_putstr_fd("cd: Too many arguments\n", 2);
		return (ERROR);
	}
	if (path[1][0] == '~')
	{
		if (env_exist("HOME") == -1)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (ERROR);
		}
		temp = ft_strjoin(getenv("HOME"), path[1] + 1);
		free(path[1]);
		path[1] = ft_strdup(temp);
		free(temp);
		if (path[1] == NULL)
		{
			ft_putstr_fd("cd: Error while changing repertories\n", 2);
			return (ERROR);
		}
	}
	if (access(path[1], F_OK) != -1)
	{
		if (chdir(path[1]) == -1)
		{
			ft_putstr_fd("cd: Error while changing repertories\n", 2);
			return (ERROR);
		}
	}
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (ERROR);
	}
	return (SUCCEED);
}

/*
* ft_echo: print the string str to the standard output
* if n_flag is not 1, it will print a newline at the end of the string
* @param: str: the string to print
*/
int	ft_echo(char **str, int n_flag) //if more then 1 -n is in place it dosent work
{
	int	i;

	i = 0;
	if (n_flag)
		i++;
	while (str[++i])
	{
		while (str[i][0] == '-' && str[i][1] == 'n')
			i++;
		ft_putstr_fd(str[i], 1);
		if (str[i + 1])
			ft_putstr_fd(" ", 1);
	}
	if (n_flag != 1)
		ft_putstr_fd("\n", 1);
	return (SUCCEED);
}

/*
* ft_pwd: print the current working directory to the standard output
*/
int	ft_pwd(void)
{
	printf("pwdio\n");
	char	*pwd;

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
int	ft_env(void)
{
	printf("envio\n");
	int	i;

	i = -1;
	while (g_global.environ[++i] != NULL)
	{
		ft_putstr_fd(g_global.environ[i], 1);
		ft_putstr_fd("\n", 1);
	}
	return (SUCCEED);
}