/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 19:53:18 by beaudibe          #+#    #+#             */
/*   Updated: 2023/03/24 19:53:18 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_history(void)
{
	int i;

	i = -1;
	while (g_global.history[++i])
	{
		ft_putstr_fd("\t", 1);
		ft_putnbr_fd(i + 1, 1);
		ft_putstr_fd("\t", 1);
		ft_putstr_fd(g_global.history[i], 1);
		ft_putstr_fd("\n", 1);
	}
	return (SUCCEED);
}

int	ft_add_history(char *line)
{
	static int	nb_history;
	int i;
	char **tmp;

	if (!line)
		return (ERROR);
	nb_history++;
	add_history(line);
	i = -1;
	tmp = malloc(sizeof(char *) * (nb_history + 1));
	if (!tmp)
		return (ERROR);
	while (g_global.history[++i])
	{
		tmp[i] = ft_strdup(g_global.history[i]);
		free(g_global.history[i]);
	}
	tmp[i] = ft_strdup(line);
	tmp[i + 1] = NULL;
	free(g_global.history);
	g_global.history = tmp;
	return (SUCCEED);
}

void	ft_clear_history()
{
	int i;

	i = -1;
	clear_history();
	while (g_global.history[++i])
	{
		free(g_global.history[i]);
	}
	free(g_global.history);
}
