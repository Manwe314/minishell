/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_meta_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:14:05 by lkukhale          #+#    #+#             */
/*   Updated: 2023/05/22 18:39:54 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char	*make_path_one(char *input)
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
				//printf("before-buffer: %s\n", buffer);
				buffer = ft_handle_dollar(buffer);
				//printf("after-buffer: %s\n", buffer);
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
	{
		arguments[index] = ft_strdup(buffer);
		i++;
	}
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

	if (size != 0)
	{
		arguments = (char **)malloc(sizeof(char *) * (size + 1));
		put_in_arguments_one(input, arguments, quote_pair);
		remove_path(arguments);
	}
	else
		return (0);
	return (arguments);
}*/

int	is_meta_char(char in)
{
	if (in == 39 || in == 34 || in == 36 || in == 60 || in == 62 || in == 124)
		return (1);
	return (0);
}

int	quoted_flag_size(char *input, int *quote_pair)
{
	int i;
	int size;

	size = 0;
	while (1)
	{
		i = quote_pair[0];
		while (++i != quote_pair[1])
			if (is_meta_char(input[i]) && (input[i] != '$' || input[quote_pair[0]] != 34))
				size++;
		quote_pair = find_quote_pairs(input, i + 1);
		if (quote_pair[0] != 0 && quote_pair[1] == 0)
			return (-1);
		else if (quote_pair[0] == 0 && quote_pair[1] == 0)
			break ;
	}
	return (size);
}

int flag_quoted_meta(char *input, int *quote_pair)
{
	int i;
	int j;
	int	quotes_count;
	int	size;

	quotes_count = 0;
	size = quoted_flag_size(input, quote_pair);
	if (size == -1)
		return (-1);
	j = -1;
	g_global.quoted_flags = (int *)malloc(sizeof(int) * (size + 1));
	quote_pair = find_quote_pairs(input, 0);
	while (1)
	{
		quotes_count++;
		i = quote_pair[0];
		while (++i != quote_pair[1])
			if (is_meta_char(input[i]) && (input[i] != '$' || input[quote_pair[0]] != 34))
				g_global.quoted_flags[++j] = i - quotes_count;
		quote_pair = find_quote_pairs(input, i + 1);
		if (quote_pair[0] == 0 && quote_pair[1] == 0)
			break ;
		else
			quotes_count++;
	}
	g_global.quoted_flags[++j] = -1;
	return 0;
}

char *remove_quotes(char *input, int *quote_pair)
{
	int i;
	char *new_input;

	i = 0;
	quote_pair = find_quote_pairs(input, 0);
	new_input = 0;
	while (input[i] != '\0')
	{
		if(i != quote_pair[0])
			new_input = ft_strjoingnl(new_input, ft_substr(input, i, quote_pair[0] - i));
		i = quote_pair[0];
		if (input[i] == 34)
			new_input = ft_strjoingnl(new_input, ft_handle_dollar(ft_substr(input, i + 1, quote_pair[1] - quote_pair[0] - 1)));
		else
			new_input = ft_strjoingnl(new_input, ft_substr(input, i + 1, quote_pair[1] - quote_pair[0] - 1));
		i = quote_pair[1];
		i++;
		quote_pair = find_quote_pairs(input, i);
		if (quote_pair[0] == 0 && quote_pair[1] == 0)
			break ;
	}
	if (input[i] != '\0')
		new_input = ft_strjoingnl(new_input, ft_substr(input, i, ft_strlen(input) - i));
	free(input); //this makes free error but idk why
	return (new_input);
}

void execute_case_one(char *input, char **envp)
{
	int	*quote_pair;
	char	*new_input;
	/*char	*path;
	char	**arguments;*/

	quote_pair = find_quote_pairs(input, 0);
	//printf ("pair: \nFirst : %d\nSecond: %d\n", quote_pair[0], quote_pair[1]);
	if (quote_pair[0] == 0 && quote_pair[1] == 0)
	{
		//printf("%s\n", input);
		//printf("%s\n", ft_handle_dollar(input));
		handle_input(ft_handle_dollar(input), envp);
		return ;
	}
	if (quote_pair[0] != 0 && quote_pair[1] == 0)
	{
		//handle error here
		return ;
	}
	// with $ dosent work
	// if $ is in: " " it expands but dosent work.
	if (flag_quoted_meta(input, quote_pair) == -1)
		return ; // error case
	new_input = remove_quotes(input, quote_pair);
	handle_input(new_input, envp);

	/*arguments = make_arguments_one(input, quote_pair);
	path = make_path_one(arguments[0]);
	printf("%s\n", path);
	if (path == 0)
	{
		path = ft_strjoin(arguments[0], ": Command Not Found\n");
		free(path);
		ft_putstr_fd(path, 2);
		free_split(arguments);
		return ;
	}
	execute_command(path, arguments, g_global.environ);*/

	// need to handle $HOME/exec and "$HOME/exec"
}
