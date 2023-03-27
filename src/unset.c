/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2023/03/24 10:45:39 by beaudibe          #+#    #+#             */
/*   Updated: 2023/03/24 10:45:39 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
* ft_unset : unset a variable from the environnement
* @str : the name variable to unset
*/

/*
? I don't think knowing if this function succeed or not is useful
*/
int	ft_unset(char *str)
{
	int i;

	i = -1;
	if (str == NULL)
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return (ERROR);
	}
	while (g_global.environ[++i])
	{
		if (ft_strncmp(g_global.environ[i], str, ft_strlen(str)) == 0)
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
