/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:45:39 by beaudibe          #+#    #+#             */
/*   Updated: 2023/03/24 10:45:39 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset_str(char **str)
{
	int	i;
	int	j;

	i = 0;
	if (!str[1])
		return (0);
	while (str[++i])
		j = ft_unset(str[i]);
	return (j);
}

int	ft_unset(char *str)
{
	int	i;

	i = -1;
	while (g_global.environ[++i])
	{
		if ((ft_strncmp(g_global.environ[i], str, ft_strlen(str)) == 0)
			&& g_global.environ[i][ft_strlengnl(str)] == '=')
		{
			free(g_global.environ[i]);
			while (g_global.environ[i + 1])
			{
				g_global.environ[i] = ft_strdup(g_global.environ[i + 1]);
				free(g_global.environ[i + 1]);
				i++;
			}
			g_global.environ[i] = NULL;
			return (SUCCEED);
		}
	}
	return (ERROR);
}
