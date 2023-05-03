/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:38:55 by lkukhale          #+#    #+#             */
/*   Updated: 2023/05/03 20:20:43 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_input()
{
	char* input;

	input = readline("minishell$ ");
	if (input == NULL)
		return (NULL);
	if (input[ft_strlen(input) - 1] == '\n')
		input[ft_strlen(input) - 1] = '\0';
	return (input);
}

int	detect_path_executable(char *input)
{
	int	i;
	int	is_path;

	i = 0;
	is_path = 0;
	//printf("input: %s\n", input);
	while (input[i] != ' ' && input[i] != '\0')
	{
		if (input[i] == '/')
		{
			is_path = 1;
			break ;
		}
		i++;
	}
	if (input[0] == '~' && is_path == 1 && input[1] == '/')
		is_path = 2;
	if (input[0] == '~' && is_path == 1 && input[1] != '/')
		is_path = 3;
	return (is_path);
}

int	detect_meta_chars(char *input)
{
	int	i;
	int casse;
				// _ | 1 | 1 2 | 1 2 3 | 2 | 2 3 | 3 | 1 3 / 0 | 1 | 3 | 7 | 2 | 6 | 4 | 5 |
	casse = 0;
	i = 0;
	while (input[i] != '\0')
	{
		// quotes ' and " and variables $
		if (input[i] == 39 || input[i] == 34 || input[i] == 36)
		{
			casse += 1;
			break;
		}
		i++;
	}
	i = 0;
	while (input[i] != '\0')
	{
		// redirections < and > and << and >>
		if (input[i] == 60 || input[i] == 62)
		{
			casse += 2;
			break;
		}
		i++;
	}
	i = 0;
	while (input[i] != '\0')
	{
		//  pipes |
		if (input[i] == 124)
		{
			casse += 4;
			break;
		}
		i++;
	}
	return (casse);
}

int	get_insert_size(char *input)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while(input[i] != '\0')
	{
		if (input[i] == '>')
		{
			if (i - 1 >= 0 && input[i - 1] != ' ' && input[i - 1] != '>' && input[i - 1] != '<')
				size++;
			if (i + 1 < ft_strlengnl(input) && input[i + 1] != ' ' && input[i + 1] != '>')
				size++;
			size++;
			i++;
		}
		if (input[i] == '<')
		{
			if ( i - 1 >= 0 && input[i - 1] != ' ' && input[i - 1] != '<' && input[i - 1] != '>')
				size++;
			if ( i + 1 < ft_strlengnl(input)  && input[i + 1] != ' ' && input[i + 1] != '<')
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
	int	i;
	int	j;
	int	size;
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
	return(new_input);
}

int	redirect_case(char **arguments, int i)
{
	if (ft_strlengnl(arguments[i]) == 1 && (arguments[i][0] == '>' || arguments[i][0] == '<'))
		return (1);
	if (ft_strlengnl(arguments[i]) > 1 && (arguments[i][0] == '>' || arguments[i][0] == '<'))
		return (2);
	if (i != 0 && (arguments[i - 1][0] == '>' || arguments[i - 1][0] == '<'))
		return (-1);
	return (0);
}

int	get_fd_size(char **arguments)
{
	int i;
	int size;

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

char	*set_up_execution_two(char **arguments)
{
	char	*input;
	char	*temp;
	int	i;
	int j;

	i = 0;
	input = 0;
	j = 0;
	g_global.fds = (int*)malloc(sizeof(int) * get_fd_size(arguments));
	while (arguments[i] != 0)
	{
		//printf("redirect case[%d]: %d\n",i , redirect_case(arguments, i));
		if (redirect_case(arguments, i) == 0)
		{
			temp = ft_strdup(arguments[i]);
			input = ft_strjoingnl(input, temp);
			temp = input;
			input = ft_strjoin(input, " ");
			free(temp);
		}
		if (redirect_case(arguments, i) == 1)
		{
			if (arguments[i + 1] != 0 && arguments[i][0] =='<')
			{
				g_global.fds[j] = open(arguments[i + 1], O_RDONLY);
				if (g_global.fds[j] < 0)
				{
					perror("failed to open a file");// could have a custom error function here;
					return (0);
				}
				dup2(g_global.fds[j], 0);
				j++;
			}
			if (arguments[i + 1] != 0 && arguments[i][0] =='>')
			{
				g_global.fds[j] = open(arguments[i + 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
				if (g_global.fds[j] < 0)
				{
					perror("failed to create a file");// could have a custom error function here;
					return (0);
				}
				dup2(g_global.fds[j], 1);
				j++;
			}
		}
		if (redirect_case(arguments, i) == 2)
		{
			// do >> or <<
		}
		i++;
	}
	return (input);
}

void	close_fds(int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (g_global.fds[i] > 0)
			close(g_global.fds[i]);
		i++;
	}
	free(g_global.fds);
	g_global.fds = 0;
	if (dup2(g_global.save_STDIN, STDIN_FILENO) < 0)
		perror("dup2");
	if (dup2(g_global.save_STDOUT, STDOUT_FILENO) < 0)
		perror("dup2");
}

void	execute_case_two(char *input)
{
	char	*new_input;
	char	**arguments;
	int		casse;

	new_input = insert_spaces(input);
	free(input);
	arguments = ft_split(new_input, ' ');
	free(new_input);
	new_input = set_up_execution_two(arguments);
	if (new_input != 0)
	{
		casse = detect_path_executable(new_input);
		if (casse > 0)
			do_pathed_executable(new_input, casse, g_global.environ);
		if (casse == 0)
			do_base_case(new_input, g_global.environ);
	}
	close_fds(get_fd_size(arguments));
	free_split(arguments);
}

/*void	execute_case_three(char *input)
{

}

void	execute_case_four(char *input)
{

}

void	execute_case_five(char *input)
{

}

void	execute_case_six(char *input)
{

}

void	execute_case_seven(char *input)
{

}*/

void	do_meta_chars(char *input, int casse)
{
	if (casse == 1)
		execute_case_one(input);
	if (casse == 2)
		execute_case_two(input);
	/*if (casse == 3)
		execute_case_three(input);
	if (casse == 4)
		execute_case_four(input);
	if (casse == 5)
		execute_case_five(input);
	if (casse == 6)
		execute_case_six(input);
	if (casse == 7)
		execute_case_seven(input);*/
}

void	handle_input(char *input, char **envp)
{
	//printf("handle input\n");
	/*parse for metacharacters
	  if there are some, then act according to those and exit this function here
	  if there are none, then:
	  parse for relative path or absolute path executables
	  if it is a absolute or relative path command to an executable, handle that case and exit this function here
	  if it is neither a metacharacter input nor a relative/absolute path input then it must be a general executable
	  therefore try to execute the input normally
	*/
	int	casse;
	int	is_meta;
	is_meta = detect_meta_chars(input);
	if (is_meta > 0)
	{
		do_meta_chars(input, is_meta);
		return ;
	}
	casse = detect_path_executable(input);
	//printf("case: %d\n", casse);
	if (casse > 0)
	{
		do_pathed_executable(input, casse, envp);
		return ;
	}
	do_base_case(input, envp);
}
