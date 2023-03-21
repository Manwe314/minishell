/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:38:55 by lkukhale          #+#    #+#             */
/*   Updated: 2023/03/21 19:44:15 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_input()
{
	char* input;

	input = readline("minishell$ ");
	if (input == NULL)
		return (NULL);
	if (input[ft_strlen(input) - 1] == '\n')
		input[ft_strlen(input) - 1] = '\0';
	return (input);
}

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

int	detect_path_executable(char *input)
{
	int	i;
	int	is_path;

	i = 0;
	is_path = 0;
	while (input[i] != ' ')
	{
		if (input[i] == '/')
			is_path = 1;
		i++;
	}
	if (input[0] == '~' && is_path == 1)
		is_path = 2;
	if (input[0] == '~' && input[1] != '/')
		is_path = 3;
	return (is_path);
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

void do_pathed_executable(char *input, int casse, char **envp)
{
	char **arguments;
	char *path;

	arguments = ft_split(input, ' ');
	path = ft_strdup(arguments[0]);
	remove_path(arguments);
	if (casse == 1)
		execute_command(path, arguments, envp);
}

void	handle_input(char *input, char **envp)
{

	/*parse for metacharacters
	  if there are some, then act according to those and exit this function here
	  if there are none, then:
	  parse for relative path or absolute path executables
	  if it is a absolute or relative path command to an executable, handle that case and exit this function here
	  if it is neither a metacharacter input nor a relative/absolute path input then it must be a general executable
	  therefore try to execute the input normally
	*/
	int	casse;
	casse = detect_path_executable(input);
	if (casse > 0)
	{
		do_pathed_executable(input, casse, envp);
		return ;
	}
	do_base_case(input, envp);
}