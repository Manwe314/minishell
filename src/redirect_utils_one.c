/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils_one.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:49:53 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/15 21:50:21 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_fname_delim(char *input, int index)
{
	int		i;
	int		j;
	char	*fdelim;
	int		*q_pair;

	i = index + 1;
	q_pair = find_quote_pairs(input, index);
	while (input[i] == ' ')
		i++;
	j = i;
	while (input[i] != ' ' && input[i] != '\0' && input[i] != '<'
		&& input[i] != '>')
	{
		if (i == q_pair[0])
		{
			i = q_pair[1];
			q_pair = find_quote_pairs(input, q_pair[1] + 1);
		}
		i++;
	}
	fdelim = clean_redirection_token(input, j, i);
	return (fdelim);
}

int	jump_fdelim(char *input, int i)
{
	int *q_pair;

	q_pair = find_quote_pairs(input, i);
	while (input[i] == ' ' || input[i] == '<' || input[i] == '>')
		i++;
	while (input[i] != ' ' && input[i] != '\0' && input[i] != '<'
		&& input[i] != '>')
	{
		if (i == q_pair[0])
		{
			i = q_pair[1];
			q_pair = find_quote_pairs(input, q_pair[1] + 1);
		}
		i++;
	}
	return (i);
}