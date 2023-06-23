/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:30:29 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/24 01:08:44 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_exist(char *str)
{
	int	i;

	i = -1;
	while (g_global.environ[++i])
		if ((ft_strncmp(g_global.environ[i], str, ft_strlen(str)) == 0)
			&& g_global.environ[i][ft_strlengnl(str)] == '=')
			return (i);
	return (-1);
}

int	ft_env(void)
{
	int	i;

	i = -1;
	while (g_global.environ[++i] != NULL)
	{
		ft_putstr_fd(g_global.environ[i], 1);
		ft_putstr_fd("\n", 1);
	}
	return (SUCCEED);
}
