/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expoort_four.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:28:49 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/16 15:51:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_bounds(char *number)
{
	if (ft_strlengnl(number) == 10 && ft_strncmp("2147483647", number, 10) < 0)
		return (1);
	if (ft_strlengnl(number) >= 11 && number[0] != '-')
		return (1);
	if (ft_strlengnl(number) == 11 &&
		ft_strncmp("-2147483647", number, 11) < 0)
		return (1);
	if (ft_strlengnl(number) >= 12)
		return (1);
	return (0);
}

int	check_char(char *number)
{
	int	i;

	i = 0;
	if (number[0] == '-')
		i++;
	while (number[i] != '\0')
	{
		if (number[i] < '0' || number[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	ft_export_str(char **str)
{
	if (!str[1])
		return (ft_print_env_alphabeticaly());
	return (export(str));
}