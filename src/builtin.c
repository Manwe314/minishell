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
		if ((ft_strncmp(g_global.environ[i], str, ft_strlen(str)) == 0) \
		 && g_global.environ[i][ft_strlengnl(str)] == '=')
			return (i);
	return (-1);
}

int sub_cd_one(void)
{
	if (env_exist("HOME") == -1)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (ERROR);
	}
	return (SUCCEED);
}

char *sub_cd_four(char *str)
{
	char *temp;

	if (str != 0)
		temp = handle_dollar(ft_strjoin(getenv("HOME"), str + 1));
	else
		temp = ft_strdup(getenv("HOME"));
	return (temp);
}

void sub_cd_two(char *temp)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(temp, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

int sub_cd_three(char *temp)
{
	if (chdir(temp) == -1)
	{
		ft_putstr_fd("cd: Error while changing repertories\n", 2);
		free(temp);
		return (ERROR);
	}
	return (SUCCEED);
}

int	ft_cd(char **path)
{
	char *temp;

	if (path[1] == 0 || path[1][0] == '~')
	{
		if (sub_cd_one() == ERROR)
			return (ERROR);
		else
			temp = sub_cd_four(path[1]);
	}
	else
		temp = handle_dollar(ft_strdup(path[1]));
	if (access(temp, F_OK) != -1)
	{
		if (sub_cd_three(temp) == ERROR)
			return (ERROR);
		free(temp);
	}
	else
	{
		sub_cd_two(temp);
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

int	ft_echo(char **str)
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

int	ft_pwd(void)
{
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

int	ft_env(void)
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