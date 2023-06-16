/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:54:00 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/16 15:00:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	return (envp[i] + 5);
}

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
		free(temp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		i++;
	}
	return (0);
}

void	do_base_case(char *input, char **envp)
{
	char	*path;
	char	**exectable_components;
	char	**individual_paths;
	char	*command;

	path = get_path(envp);
	individual_paths = ft_split(path, ':');
	exectable_components = ft_split(input, ' ');
	if (ft_is_buitin(exectable_components) == SUCCEED)
	{
		g_global.exit_status = ft_execute_command_builtin(exectable_components);
		free_split(individual_paths);
		free_split(exectable_components);
		return ;
	}
	command = get_command(exectable_components[0], individual_paths);
	if (command == 0)
	{
		command = ft_strjoin(exectable_components[0], ": Command Not Found\n");
		ft_putstr_fd(command, 2);
		free(command);
		free_split(individual_paths);
		free_split(exectable_components);
		return ;
	}
	if (ft_strncmp(command, "/usr/bin/cat", 12) == 0)
		g_global.is_cat = 1;
	execute_command(command, exectable_components, envp);
}
