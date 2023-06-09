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
		if ((ft_strncmp(g_global.environ[i], str, ft_strlen(str)) == 0) && g_global.environ[i][ft_strlengnl(str)] == '=')
			return (i);
	return (-1);
}

/*
* ft_cd: change the current working directory to the one specified in path
* will check if the path exists and if the user has the right to access it
* @param: path: the path to the new working directory
*/
int	ft_cd(char **path)
{
	char *temp;

	if (path[1] == 0 || path[1][0] == '~')
	{
		if (env_exist("HOME") == -1)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (ERROR);
		}
		if (path[1] != 0)
			temp = handle_dollar(ft_strjoin(getenv("HOME"), path[1] + 1));
		else
			temp = ft_strdup(getenv("HOME"));
		if (temp == NULL)
		{
			ft_putstr_fd("cd: Error while changing repertories\n", 2);
			return (ERROR);
		}
	}
	else
		temp = handle_dollar(ft_strdup(path[1]));
	if (access(temp, F_OK) != -1)
	{
		if (chdir(temp) == -1)
		{
			ft_putstr_fd("cd: Error while changing repertories\n", 2);
			free(temp);
			return (ERROR);
		}
		free(temp);
	}
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(temp, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(temp);
		return (ERROR);
	}
	return (SUCCEED);
}

int is_flaged(char *str)
{
	int i;

	if (str == 0)
		return (0);
	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i] == 'n' && str[i] != '\0')
		i++;
	if (str[i] != '\0')
		return (0);
	else
		return (1);
}

/*
* ft_echo: print the string str to the standard output
* if n_flag is not 1, it will print a newline at the end of the string
* @param: str: the string to print
*/
int	ft_echo(char **str) //if more then 1 -n is in place it dosent work
{
	int	i;
	int flag;

	i = 0;
	flag = is_flaged(str[1]);
	while (str[++i])
	{
		while (is_flaged(str[i]))
			i++;
		ft_putstr_fd(str[i], 1);
		if (str[i + 1])
			ft_putstr_fd(" ", 1);
	}
	if (flag != 1)
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