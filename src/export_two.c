/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:26:20 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/19 20:54:35 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int is_invalid_identifier(char a)
{
	if (a >= 0 && a <= 64)
		return (1);
	if (a >= 91 && a <= 96)
		return (1);
	if (a >= 123)
		return (1);
	return (0);
}

int does_match(char *str, int v_flag)
{
	int i;
	int len;

	i = 0;
	if (str == 0 || v_flag == 1)
		return (0);
	while (str[i] != '=' && str[i] != '\0')
		i++;
	len = i;
	i = 0;
	while (g_global.environ[i] != 0)
	{
		if ((ft_strncmp(g_global.environ[i], str, len) == 0 ) \
		&& (g_global.environ[i][len] == '='))
			return (1);
		i++;
	}
	return (0);
}

int match_and_validate(char **arguments, int *err)
{
	int i;
	int size;
	int v_flag;

	i = 1;
	size = 0;
	v_flag = 0;
	while (arguments[i] != 0)
	{
		if (!is_valid_exp(arguments[i], 1))
		{
			*err = 1;
			size++;
			v_flag = 1;
		}
		if (does_match(arguments[i], v_flag))
			size++;
		v_flag = 0;
		i++;
	}
	return (size);
}

int get_new_env_size(char **arguments, int *err)
{
	int env_size;
	int removal_size;
	int i;

	env_size = 0;
	while (g_global.environ[env_size] != 0)
		env_size++;
	i = 0;
	while (arguments[i] != 0)
		i++;
	env_size = env_size + i;
	removal_size = match_and_validate(arguments, err);
	return (env_size - removal_size);
}