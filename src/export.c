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
