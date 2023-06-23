/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hall <hall@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:31:04 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/23 22:17:15 by hall             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_old_pwd(void)
{
	int	i;

	i = 0;
	while (g_global.environ[i] != 0)
	{
		if (ft_strncmp(g_global.environ[i], "OLDPWD=", 7) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	find_pwd(void)
{
	int	i;

	i = 0;
	while (g_global.environ[i] != 0)
	{
		if (ft_strncmp(g_global.environ[i], "PWD=", 4) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	make_pwd(char *pwd, int flag)
{
	int		i;
	char	*variable;
	char	**env;

	if (flag == 0)
		variable = ft_strjoin("OLDPWD=", pwd);
	if (flag == 1)
		variable = ft_strjoin("PWD=", pwd);
	env = (char **)malloc(sizeof(char *) * (split_size(g_global.environ) + 2));
	i = -1;
	while (g_global.environ[++i] != 0)
		env[i] = ft_strdup(g_global.environ[i]);
	env[i] = variable;
	env[++i] = 0;
	free_split(g_global.environ);
	g_global.environ = env;
}

void	update_pwd(char *pwd, int flag)
{
	int		i;
	char	*temp;

	if (flag == 0)
		i = find_old_pwd();
	if (flag == 1)
		i = find_pwd();
	if (i < 0)
		make_pwd(pwd, flag);
	else
	{
		temp = g_global.environ[i];
		if (flag == 0)
			g_global.environ[i] = ft_strjoin("OLDPWD=", pwd);
		if (flag == 1)
			g_global.environ[i] = ft_strjoin("PWD=", pwd);
		free(temp);
	}
	free(pwd);
}

int	ft_pwd(void)
{
	int		i;
	char	*pwd;

	i = -1;
	while (g_global.environ[++i] != 0)
		if (ft_strncmp(g_global.environ[i], "PWD=", 4) == 0)
			break ;
	if (g_global.environ[i] == 0)
		pwd = getcwd(NULL, 0);
	else
		pwd = ft_strdup(g_global.environ[i] + 4);
	if (pwd == NULL)
	{
		ft_putstr_fd(
			"pwd: Error while getting the current working directory\n", 2);
		return (ERROR);
	}
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free(pwd);
	return (SUCCEED);
}
