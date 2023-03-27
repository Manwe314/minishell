/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2023/03/20 14:06:20 by beaudibe          #+#    #+#             */
/*   Updated: 2023/03/20 14:06:20 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* ft_print_env_alphabeticaly: print the environment variables in
* alphabetical order
*/
int	ft_print_env_alphabeticaly(void)
{
	char	**env;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (g_global.environ[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (ERROR);
	i = -1;
	while (g_global.environ[++i])
	{
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
			env[j] = ft_strdup(env[j - 1]);
			free(env[j - 1]);
			env[j - 1] = ft_strdup(tmp);
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

int	ft_change_env(char *name, char *value)
{
	int i;
	int j;
	char *tmp;

	i = -1;
	while (g_global.environ[++i])
	{
		j = 0;
		while (g_global.environ[i][j] != '=' && g_global.environ[i][j] != '\0')
			j++;
		if (ft_strncmp(g_global.environ[i], name, j) == 0)
		{
			tmp = ft_strdup(g_global.environ[i]);
			free(g_global.environ[i]);
			g_global.environ[i] = ft_strjoin(name, value);
			free(tmp);
			return (SUCCEED);
		}
	}
	return (ERROR);
}

int	ft_add_env(char *name, char *value)
{
	int		i;
	char	**tmp;

	i = 0;
	while (g_global.environ[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		return (ERROR);
	i = -1;
	while (g_global.environ[++i])
	{
		tmp[i] = ft_strdup(g_global.environ[i]);
		if (!tmp[i])
		{
			while (--i >= 0)
				free(tmp[i]);
			free(tmp);
			return (ERROR);
		}
		free(g_global.environ[i]);
	}
	free(g_global.environ);
	tmp[i] = ft_strjoin(name, value);
	tmp[i + 1] = NULL;
	g_global.environ = tmp;
	return (SUCCEED);
}

/*
* ft_export: add the variable name to the environment with the value value
* if the variable already exists, it will change its value to value
* if no argument is given, it will print the environment variables
* @param: str: the string in format "name=value" to add to the environment
*/

/*
! if a malloc fails in ft_change env, the function will try ft_add_env
*/
int	ft_export(char *str)
{
	char	*name;
	char	*value;
	int		return_value;

	return_value = 0;
	if (!str)
		return (ft_print_env_alphabeticaly());
	if (ft_strchr(str, '=') == NULL)
	{
		name = str;
		value = ft_strdup("=");
		if (!value)
			return (ERROR);
	}
	else
	{
		name = ft_substr(str, 0, ft_strchr(str, '=') - str);
		if (!name)
			return (ERROR);
		value = ft_substr(str, ft_strchr(str, '=') - str, ft_strlen(str)
				- ft_strlen(name));
		if (!value)
		{
			free(name);
			return (ERROR);
		}
	}
	if (ft_change_env(name, value) == ERROR)
		return_value = ft_add_env(name, value);
	free(name);
	free(value);
	return (return_value);
}
