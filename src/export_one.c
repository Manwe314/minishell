/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:25:30 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/28 16:09:42 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_args(char **args, char *str)
{
	int	i;
	int	len;

	i = 1;
	len = 0;
	if (args[0] == 0)
		return (-1);
	while (str[len] != '=' && str[len] != '\0')
		len++;
	while (args[i] != 0)
	{
		if ((ft_strncmp(args[i], str, len) == 0) \
		&& (args[i][len] == '=' || args[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

char	*find_and_add(char **args, char *str)
{
	int		id;
	char	*new;
	char	*tmp;

	id = is_in_args(args, str);
	new = ft_strdup(args[id]);
	if (ft_strchr(new, '=') == 0)
	{
		tmp = ft_strjoin(new, "=");
		free(new);
		new = tmp;
	}
	return (new);
}

char	*put_in_env(char *str)
{
	char	*new;
	char	*tmp;

	new = ft_strdup(str);
	if (ft_strchr(new, '=') == 0)
	{
		tmp = ft_strjoin(new, "=");
		free(new);
		new = tmp;
	}
	return (new);
}

char	**build_new_env(char **arguments, int size)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = (char **)malloc(size * sizeof(char *));
	i = -1;
	j = 1;
	while (g_global.environ[++i] != 0)
	{
		if (is_in_args(arguments, g_global.environ[i]) >= 0)
			new_env[i] = find_and_add(arguments, g_global.environ[i]);
		else
			new_env[i] = ft_strdup(g_global.environ[i]);
	}
	while (arguments[j] != 0)
	{
		if (is_in_args(g_global.environ, arguments[j]) == -1
			&& is_valid_exp(arguments[j], 0))
			new_env[i++] = put_in_env(arguments[j]);
		j++;
	}
	new_env[i] = 0;
	return (new_env);
}

int	export(char **arguments)
{
	int		has_error;
	char	**new_env;

	has_error = 0;
	arguments = remove_duplicates(arguments);
	new_env = build_new_env(arguments, \
				get_new_env_size(arguments, &has_error));
	free_split(g_global.environ);
	free_split(arguments);
	g_global.environ = new_env;
	return (has_error);
}
