/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_four.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 22:58:39 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/24 00:56:51 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sub_clean_rt_two_hdoc(char *token, int i, int j, int *q_pair)
{
	if (i != j && j <= i)
		token = ft_strjoingnl(token, \
		ft_substr(g_global.input, j, i - j));
	if (g_global.input[q_pair[0]] == 34)
		token = ft_strjoingnl(token, ft_substr(g_global.input, q_pair[0] + 1, \
		q_pair[1] - q_pair[0] - 1));
	else
		token = ft_strjoingnl(token, ft_substr(g_global.input, q_pair[0] + 1, \
		q_pair[1] - q_pair[0] - 1));
	return (token);
}

char	*sub_clean_rt_one_hdoc(char *token, int i, int end, int *q_pair)
{
	int	j;

	j = i;
	while (i != end)
	{
		while (i != q_pair[0] && i != end)
			i++;
		if (i == q_pair[0] && q_pair[1] != 0)
		{
			token = sub_clean_rt_two_hdoc(token, i, j, q_pair);
			i = q_pair[1] + 1;
			j = i;
			q_pair = find_quote_pairs(g_global.input, i);
			if (i == q_pair[0])
				i--;
		}
		else
			token = ft_strjoingnl(token, \
					ft_substr(g_global.input, j, i - j));
		if (i != end)
			i++;
	}
	return (token);
}

char	*clean_redirection_token_hdoc(char *input, int start, int end)
{
	int		i;
	int		*q_pair;
	char	*token;

	q_pair = find_quote_pairs(input, start);
	i = start;
	token = 0;
	g_global.input = input;
	token = sub_clean_rt_one_hdoc(token, i, end, q_pair);
	return (token);
}

char	*get_fname_delim_hdoc(char *input, int index)
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
	fdelim = clean_redirection_token_hdoc(input, j, i);
	return (fdelim);
}
