/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_meta_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:14:05 by lkukhale          #+#    #+#             */
/*   Updated: 2023/04/21 19:18:55 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_path_one(char *input)
{
	char 	**arguments;
	char	**individual_paths;
	char	*path;
	int		casse;

	path = 0;
	arguments = ft_split(input, ' ');
	casse = detect_path_executable(arguments[0]);
	if (casse == 1)
		path = ft_strdup(arguments[0]);
	if (casse == 2)
		path = expand_home_directory(arguments[0], g_global.environ);
	if (casse == 3)
		path = clean_home_path(arguments[0], g_global.environ);
	if (casse == 0)
	{
		path = get_path(g_global.environ);
		individual_paths = ft_split(path, ':');
		path = get_command(arguments[0], individual_paths);
		free_split(individual_paths);
	}
	free_split(arguments);
	return (path);
}

int	init_size_arguments_one(char *input, int *quote_pair)
{
	int	size;
	int	i;
	int	j;

	size = 0;
	i = 0;
	while (input[i] != '\0')
	{
		if (i == quote_pair[0])
		{
			i = quote_pair[1];
			quote_pair = find_quote_pairs(input, i + 1);
			if (quote_pair[0] != 0 && quote_pair[1] == 0)
				return (0);
		}
		if (input[i] == ' ')
		{
			if (!is_begining(input, i))
			{
				j = i;
				while (input[j] == ' ' && input[j] != '\0')
					j++;
				if (input[j] != '\0')
					size++;
				i = j - 1;
			}
			else
				j = i + 1;

		}
		i++;
	}
	return (size + 1);
}

void	put_in_arguments_one(char *input, char **arguments, int *quote_pair)
{
	int	i;
	int	j;
	int	index;
	char *buffer;

	quote_pair = find_quote_pairs(input, 0);
	i = 0;
	j = 0;
	index = 0;
	buffer = 0;
	while (input[i] != '\0')
	{
		if (i == quote_pair[0])
		{
			buffer = ft_strjoingnl(buffer, ft_substr(input, j, i - j));
			buffer = ft_strjoingnl(buffer, ft_substr(input, i + 1, quote_pair[1] - quote_pair[0] - 1));
			if (input[i] == 34)
			{
				// buffer = handle $
			}
			i = quote_pair[1];
			j = quote_pair[1] + 1;
			quote_pair = find_quote_pairs(input, i + 1);
		}
		if (input[i] == ' ')
		{
			if (!is_begining(input, i))
			{
				if ((i - j) > 1)
					buffer = ft_strjoingnl(buffer, ft_substr(input, j, i - j));
				arguments[index] = ft_strdup(buffer);
				free(buffer);
				index++;
				buffer = 0;
				while (input[i] == ' ')
					i++;
				j = i;
				i--;
			}
			else
				j = i + 1;
		}
		i++;
	}
	if ((i - j) > 1)
		buffer = ft_strjoingnl(buffer, ft_substr(input, j, i - j));
	if (buffer == 0)
		arguments[index] = 0;
	else
		arguments[index] = ft_strdup(buffer);
	free(buffer);
	if ((i - j) != 0)
	{
		index++;
		arguments[index] = 0;
	}
}

char	**make_arguments_one(char *input, int *quote_pair)
{
	char **arguments;
	int	size;

	size = init_size_arguments_one(input, quote_pair);
	//printf("%d\n", size);
	if (size != 0)
	{
		arguments = (char **)malloc(sizeof(char *) * size + 1);
		put_in_arguments_one(input, arguments, quote_pair);
		remove_path(arguments);
	}
	else
		return (0);
	return (arguments);
}

void	execute_case_one(char *input)
{
	int	*quote_pair;
	char	*path;
	char	**arguments;

	quote_pair = find_quote_pairs(input, 0);
	//printf ("pair: \nFirst : %d\nSecond: %d\n", quote_pair[0], quote_pair[1]);
	if (quote_pair[0] == 0 && quote_pair[1] == 0)
	{
		//handle $ function here
		return ;
	}
	if (quote_pair[0] != 0 && quote_pair[1] == 0)
	{
		//handle error here
		return ;
	}
	//printf("henlo\n");
	path = make_path_one(input);
	arguments = make_arguments_one(input, quote_pair);
	execute_command(path, arguments, g_global.environ);
	// need to handle $HOME/exec and "$HOME/exec"
}
