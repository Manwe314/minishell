/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_paths_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:48:19 by lkukhale          #+#    #+#             */
/*   Updated: 2023/03/22 19:57:43 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void do_pathed_executable(char *input, int casse, char **envp)
{
	char **arguments;
	char *path;

	arguments = ft_split(input, ' ');
	if (casse == 1)
	{
		path = ft_strdup(arguments[0]);
		remove_path(arguments);
		execute_command(path, arguments, envp);
	}
	if (casse == 2)
	{
		path = expand_home_directory(arguments[0], envp);
		remove_path(arguments);
		execute_command(path, arguments, envp);
	}
	if (casse == 3)
	{
		path = clean_home_path(arguments[0], envp);
		remove_path(arguments);
		execute_command(path, arguments, envp);
	}
	free(path);
	free_split(arguments);
}

void remove_path(char **arguments)
{
	int	i;

	i = ft_strlen(arguments[0]);
	while (arguments[0][i] != '/')
		i--;
	i++;
	arguments[0] = ft_substr(arguments[0], i, ft_strlen(arguments[0]) - i);
}

char	*expand_home_directory(char *path, char **envp)
{
	char	*home;
	char	*new_path;


	home = get_home(envp);
	new_path = ft_strdup(path + 1);
	new_path = ft_strjoin(home, new_path);
	return (new_path);
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
	return (new_path);
}