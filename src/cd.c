/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:22:58 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/19 22:07:33 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sub_cd_one(void)
{
	if (env_exist("HOME") == -1)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (ERROR);
	}
	return (SUCCEED);
}

char	*sub_cd_four(char *str)
{
	char	*temp;

	if (str != 0)
		temp = handle_dollar(ft_strjoin(getenv("HOME"), str + 1));
	else
		temp = ft_strdup(getenv("HOME"));
	return (temp);
}

void	sub_cd_two(char *temp)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(temp, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

int	sub_cd_three(char *temp)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	update_pwd(pwd, 0);
	if (chdir(temp) == -1)
	{
		ft_putstr_fd("cd: Error while changing repertories\n", 2);
		free(temp);
		return (ERROR);
	}
	pwd = getcwd(NULL, 0);
	update_pwd(pwd,1);
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