/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:31:01 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/24 17:32:33 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(int pip0, int pip1, char *delim)
{
	char	*input;
	char	*temp;

	while (1)
	{
		close(pip0);
		input = readline("> ");
		if ((ft_strncmp(delim, input,
					(unsigned int)ft_strlengnl(delim)) == 0
				&& ft_strlen(delim) == ft_strlen(input)) || input == NULL
			|| g_global.ctrl_c == 1)
		{
			free(input);
			break ;
		}
		temp = input;
		input = ft_strjoin(input, "\n");
		free(temp);
		g_global.here_doc = ft_strjoingnl(g_global.here_doc, input);
	}
	ft_putstr_fd(g_global.here_doc, pip1);
	close(pip1);
	return (0);
}
