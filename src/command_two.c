/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:58:12 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/24 01:09:34 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_home_directory(char *path, char **envp)
{
	char	*home;
	char	*new_path;

	home = get_home(envp);
	new_path = ft_strdup(path + 1);
	new_path = ft_strjoin(home, new_path);
	free(home);
	return (new_path);
}

char	*get_home(char **envp)
{
	int		i;
	char	*home;

	i = 0;
	while (ft_strncmp(envp[i], "HOME=", 5) != 0)
		i++;
	home = ft_strdup(envp[i] + 5);
	return (home);
}

char	*return_user(char *path)
{
	int		i;
	int		size;
	char	*user;

	i = 1;
	size = 0;
	while (path[i] != '/')
	{
		size++;
		i++;
	}
	user = malloc(size * sizeof(char));
	i = 1;
	while (path[i] != '/')
	{
		user[i - 1] = path[i];
		i++;
	}
	return (user);
}

int	home_begin_size(char *home)
{
	int	i;

	i = ft_strlen(home) - 1;
	while (home[i] != '/')
		i--;
	return (i + 1);
}

char	*clean_home_path(char *path, char **envp)
{
	char	*home;
	char	*user;
	char	*new_path;
	int		sub_size;

	home = get_home(envp);
	user = return_user(path);
	sub_size = home_begin_size(home);
	home = ft_substr(home, 0, sub_size);
	new_path = ft_strjoin(home, user);
	sub_size = 0;
	while (path[sub_size] != '/')
		sub_size++;
	new_path = ft_strjoin(new_path, (path + sub_size));
	free(user);
	free(home);
	return (new_path);
}
