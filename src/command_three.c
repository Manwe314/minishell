/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:59:08 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/24 01:09:57 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_start_index(char *input, int start)
{
	int	i;

	i = start;
	while ((input[i] == ' ' || input[i] == '<' || input[i] == '>')
		&& input[i] != '\0')
	{
		if (input[i] == '<' || input[i] == '>')
			i = jump_fdelim(input, i);
		else
			i++;
	}
	return (i);
}

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != 0 && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == 0)
		return (0);
	return (envp[i] + 5);
}
