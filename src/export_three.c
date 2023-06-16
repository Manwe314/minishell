/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_three.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:27:32 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/15 21:27:48 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sub_is_valid_exp_one(char *str, int f)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (is_invalid_identifier(str[i]) == 1)
		{
			if (f != 0)
			{
				ft_putstr_fd(str, 1);
				ft_putstr_fd(" : has an invalid identifier : ", 1);
				ft_putchar_fd(str[i], 1);
				ft_putchar_fd('\n', 1);
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int	sub_is_valid_exp_two(char *str, int f)
{
	if (str[0] == '=')
	{
		if (f != 0)
		{
			ft_putstr_fd(str, 1);
			ft_putstr_fd(" : has an invalid identifier\n", 1);
		}
		return (0);
	}
	return (1);
}

int	sub_is_valid_exp_three(char *str, int f)
{
	int	i;

	i = 0;
	while (str[i] != '=')
	{
		if (is_invalid_identifier(str[i]) == 1)
		{
			if (f != 0)
			{
				ft_putstr_fd(str, 1);
				ft_putstr_fd(" : has an invalid identifier : ", 1);
				ft_putchar_fd(str[i], 1);
				ft_putchar_fd('\n', 1);
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_valid_exp(char *str, int f)
{
	if (ft_strchr(str, '=') == 0)
	{
		if (sub_is_valid_exp_one(str, f) == 0)
			return (0);
	}
	else
	{
		if (sub_is_valid_exp_two(str, f) == 0)
			return (0);
		if (sub_is_valid_exp_three(str, f) == 0)
			return (0);
	}
	return (1);
}