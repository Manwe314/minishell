/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:29:39 by lkukhale          #+#    #+#             */
/*   Updated: 2023/07/04 17:06:01 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_flaged(char *str)
{
	int	i;

	if (str == 0)
		return (0);
	i = 0;
	if (str[i] != '-')
		return (0);
	else if (str[i] == '-' && ft_strlen(str) == 1)
		return (0);
	i++;
	while (str[i] == 'n' && str[i] != '\0')
		i++;
	if (str[i] != '\0')
		return (0);
	else
		return (1);
}

int	ft_echo(char **str)
{
	int	i;
	int	flag;
	int non_flag;

	i = 1;
	non_flag = 0;
	flag = is_flaged(str[1]);
	while (str[i])
	{
		if (is_flaged(str[i]) && non_flag != 1)
			i++;
		else
		{
			non_flag = 1;
			ft_putstr_fd(str[i], 1);
			if (str[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
	}
	if (flag != 1)
		ft_putstr_fd("\n", 1);
	return (0);
}
