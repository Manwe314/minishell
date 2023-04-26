/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:54:00 by lkukhale          #+#    #+#             */
/*   Updated: 2023/03/28 17:46:42 by lkukhale         ###   ########.fr       */
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
		free (temp);
		if (access(command, 0) == 0)
			return (command);
		free (command);
		i++;
	}
	return (0);
}

void do_base_case(char *input, char **envp)
{
	char *path;
	char **exectable_components;
	char **individual_paths;
	char *command;

	path = get_path(envp);
	individual_paths = ft_split(path, ':');
	exectable_components = ft_split(input, ' ');
	command = get_command(exectable_components[0], individual_paths);
	if (command == 0)
	{
		command = ft_strjoin(exectable_components[0], ": Command Not Found\n");
		ft_putstr_fd(command, 1);
		free(command);
		free_split(individual_paths);
		free_split(exectable_components);
		return ;
	}
	execute_command(command, exectable_components, envp);
}
