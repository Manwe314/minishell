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

char **sub_print_env_one(void)
{
	char **env;
	int i;

	i = 0;
	env = (char **)malloc(sizeof(char *) * (split_size(g_global.environ) + 1));
	if (!env)
		return (0);
	while (g_global.environ[i] != 0)
	{
		env[i] = ft_strdup(g_global.environ[i]);
		i++;
	}
	env[i] = 0;
	return (env);
}

void sub_print_env_two(char **env, int i)
{
	int j;
	char *tmp;

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

int	ft_print_env_alphabeticaly(void)
{
	char	**env;
	int		i;
	int		j;

	env = sub_print_env_one();
	i = 0;
	while (env[++i])
		sub_print_env_two(env, i);
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
