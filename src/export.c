/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:06:20 by beaudibe          #+#    #+#             */
/*   Updated: 2023/03/20 14:06:20 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* ft_print_env_alphabeticaly: print the environment variables in
* alphabetical order
*/
int ft_print_env_alphabeticaly()
{
	char **env;
	char *tmp;
	int i;
	int j;

	i = 0;
	while (g_global.environ[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (ERROR);
	i = -1;
	while (g_global.environ[++i]){
		env[i] = ft_strdup(g_global.environ[i]);
	}
	env[i] = NULL;
	i = 0;
	while (env[++i])
	{
		j = i;
		while (j > 0 && ft_strncmp(env[j - 1], env[j], ft_strlen(env[j - 1])) > 0)
		{
			tmp = ft_strdup(env[j]);
			free(env[j]);
			env[j] = ft_strdup(env[j-1]);
			free(env[j-1]);
			env[j-1] = ft_strdup(tmp);
			free(tmp);
			j--;
		}
	}
	i = -1;
	while (env[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		j = -1;
		while (env[i][++j] != '=' && env[i][j] != '\0')
			ft_putchar_fd(env[i][j], 1);
		if (env[i][j] == '=')
			ft_putstr_fd("=\"", 1);
		ft_putstr_fd(env[i] + j + 1, 1);
		ft_putstr_fd("\"\n", 1);
		free(env[i]);
	}
	free(env);
	return (SUCCEED);
}

/*
* ft_export: add the variable name to the environment with the value value
* if the variable already exists, it will change its value to value
* if no argument is given, it will print the environment variables
* @param: str: the string in format "name=value" to add to the environment
*/

/*
TODO: if value doesn't exist, add the variable to the environment
! segffault when the new value is long
*/
int ft_export(char *str)
{
	int 		i;
	char		*name;
	char		*value;

	i = -1;
	if (!str)
	{
		return (ft_print_env_alphabeticaly());
	}
	if (ft_strchr(str, '=') == NULL)
	{
		name = str;
		value = "\0";
	}
	else
	{
		name = ft_substr(str, 0, ft_strchr(str, '=') - str);
		value = ft_substr(str, ft_strchr(str, '=') - str + 1, ft_strlen(str) - ft_strlen(name) - 1);
	}
	if (getenv(name))
	{
		while (g_global.environ[++i])
		{
			if (ft_strnstr(g_global.environ[i], name, ft_strlen(name)) != 0)
			{
				ft_strlcpy((g_global.environ[i] + ft_strlen(name) + 1), value, ft_strlen(value) + 1);
				free(name);
				free(value);
				return (SUCCEED);
			}
		}
	}*/
	return 0;
	//return (ft_change_env_var(name, value));
}
