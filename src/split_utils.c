/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hall <hall@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:40:01 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/23 22:24:52 by hall             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_size(char **split)
{
	int	i;

	i = 0;
	while (split[i] != 0)
		i++;
	return (i);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split == 0)
		return ;
	while (split[i] != 0)
	{
		free(split[i]);
		i++;
	}
	free(split[i]);
	free(split);
}
