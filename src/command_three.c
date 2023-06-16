/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:59:08 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/15 21:59:42 by lkukhale         ###   ########.fr       */
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
	int i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	return (envp[i] + 5);
}