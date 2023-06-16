/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_meta_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:10:13 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/16 14:50:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_insert_size(char *input)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '>')
		{
			if (i - 1 >= 0 && input[i - 1] != ' ' && input[i - 1] != '>'
				&& input[i - 1] != '<')
				size++;
			if (i + 1 < ft_strlengnl(input) && input[i + 1] != ' ' && input[i
				+ 1] != '>')
				size++;
			size++;
			i++;
		}
		if (input[i] == '<')
		{
			if (i - 1 >= 0 && input[i - 1] != ' ' && input[i - 1] != '<'
				&& input[i - 1] != '>')
				size++;
			if (i + 1 < ft_strlengnl(input) && input[i + 1] != ' ' && input[i
				+ 1] != '<')
				size++;
			size++;
			i++;
		}
		if (input[i] != '\0' && input[i] != '>' && input[i] != '<')
		{
			size++;
			i++;
		}
	}
	return (size);
}

char	*insert_spaces(char *input)
{
	int		i;
	int		j;
	int		size;
	char	*new_input;

	size = get_insert_size(input);
	//printf("original: %d\nnew: %d\ndiff: %d\n", ft_strlengnl(input), size, size - ft_strlengnl(input));
	new_input = malloc((size + 1) * sizeof(char));
	i = 0;
	j = 0;
	size = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '>' || input[i] == '<')
		{
			size = i;
			if (i - 1 >= 0 && input[i - 1] != ' ' && input[i] != input[i - 1])
			{
				new_input[j] = ' ';
				j++;
			}
			while (input[i] != '\0' && input[size] == input[i])
			{
				new_input[j] = input[i];
				i++;
				j++;
			}
			new_input[j] = ' ';
			j++;
		}
		new_input[j] = input[i];
		i++;
		j++;
	}
	new_input[j] = '\0';
	return (new_input);
}

int	redirect_case(char **arguments, int i)
{
	if (ft_strlengnl(arguments[i]) == 1 && (arguments[i][0] == '>'
			|| arguments[i][0] == '<'))
		return (1);
	if (ft_strlengnl(arguments[i]) > 1 && (arguments[i][0] == '>'
			|| arguments[i][0] == '<'))
		return (2);
	if (i != 0 && (arguments[i - 1][0] == '>' || arguments[i - 1][0] == '<'))
		return (-1);
	return (0);
}

int	get_fd_size(char **arguments)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (arguments[i] != 0)
	{
		if (arguments[i][0] == '>' || arguments[i][0] == '<')
			size++;
		i++;
	}
	return (size);
}

void	handle_heredoc(char *delim)
{
	char *input;
	char *temp;

	if (g_global.here_doc != 0)
	{
		free(g_global.here_doc);
		g_global.here_doc = 0;
	}
	if (dup2(g_global.save_STDIN, STDIN_FILENO) < 0)
		perror("here dup2");
	if (dup2(g_global.save_STDOUT, STDOUT_FILENO) < 0)
		perror("here dup2");
	while (1)
	{
		input = readline("> ");
		if ((ft_strncmp(delim, input, (unsigned int)ft_strlengnl(delim)) == 0
				&& ft_strlen(delim) == ft_strlen(input)) || input == NULL)
		{
			free(input);
			break ;
		}
		temp = input;
		input = ft_strjoin(input, "\n");
		free(temp);
		g_global.here_doc = ft_strjoingnl(g_global.here_doc, input);
	}
	if (g_global.last_out >= 0)
	{
		if (dup2(g_global.fds[g_global.last_out], STDOUT_FILENO) < 0)
			perror("last dup2");
		g_global.last_out = -1;
	}
	free(delim);
}