/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:55:26 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/15 21:57:57 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command(char *name, char **paths)
{
	char	*temp;
	char	*command;
	int		i;

	i = 0;
	while (paths[i] != 0)
	{
		temp = ft_strjoin(paths[i], "/");
		command = ft_strjoin(temp, name);
		free (temp);
		if (access(command, 0) == 0)
		{
			free_split(paths);
			return (command);
		}
		free (command);
		i++;
	}
	printf("minishell: %s: command not found\n", name);
	g_global.exit_status = 1;
	free_split(paths);
	return (0);
}

int	detect_path_executable(char *input)
{
	int	i;
	int	is_path;

	i = 0;
	is_path = 0;
	while (input[i] != ' ' && input[i] != '\0')
	{
		if (input[i] == '/')
		{
			is_path = 1;
			break ;
		}
		i++;
	}
	if (input[0] == '~' && is_path == 1 && input[1] == '/')
		is_path = 2;
	if (input[0] == '~' && is_path == 1 && input[1] != '/')
		is_path = 3;
	return (is_path);
}

char *remove_path(char *command)
{
	int	i;
	int is_slash;
	char *name;

	i = 0;
	is_slash = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '/')
			is_slash = 1;
		i++;
	}
	if (!is_slash)
		return (command);
	while (command[i] != '/')
		i--;
	i++;
	name = ft_substr(command, i, ft_strlen(command) - i);
	free(command);
	return (name);
}

char *clean_command(char *command, int casse)
{
	char *path;

	if (casse == 1)
	{
		path = ft_strdup(command);
		free(command);
	}
	if (casse == 2)
	{
		path = expand_home_directory(command, g_global.environ);
		free(command);
	}
	if (casse == 3)
		path = clean_home_path(command, g_global.environ);
	if (casse == 0)
	{
		path = get_command(command, ft_split(get_path(g_global.environ), ':'));
		free(command);
	}
	return (path);
}

char *get_clean_command(char **arguments)
{
	char *command;

	if (arguments[0] != 0)
	{
		command = ft_strdup(arguments[0]);
		arguments[0] = remove_path(arguments[0]);
		if (!ft_is_buitin(arguments))
			command = clean_command(command, detect_path_executable(command));
	}
	else
		command = 0;
	return (command);
}