/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:38:55 by lkukhale          #+#    #+#             */
/*   Updated: 2023/05/16 17:28:01 by lkukhale         ###   ########.fr       */
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
	while (input[i] != ' ' && input[i] != '\0') // if it starts with space???
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

int	is_flaged(int index)
{
	int	i;

	if (g_global.quoted_flags == 0)
		return (0);
	i = 0;
	while (g_global.quoted_flags[i] != -1)
	{
		if (g_global.quoted_flags[i] == index)
			return (1);
		i++;
	}
	return (0);
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
		if ((input[i] == 39 || input[i] == 34 || input[i] == 36) && !is_flaged(i))
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
		if ((input[i] == 60 || input[i] == 62) && !is_flaged(i))
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
		if (input[i] == 124 && !is_flaged(i))
		{
			casse += 4;
			break;
		}
		i++;
	}
	return (casse);
}

void do_meta_chars(char *input, int casse, char **envp)
{
	if (casse == 1)
		execute_case_one(input, envp);
	if (casse == 2)
		execute_case_two(input);
	if (casse == 3)
		execute_case_one(input, envp);
	if (casse == 4)
		execute_case_four(input);
	if (casse == 5)
		execute_case_one(input, envp);
	if (casse == 6)
		execute_case_four(input);
	if (casse == 7)
		execute_case_one(input, envp);
}

int get_revert_size(char *input)
{
	int i;
	int	size;

	i = 0;
	size  = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '*'  || input[i] == ';' || input[i] == '&' || input[i] == '(' || input[i] == ')' || input[i] == '!')
			size++;
		i++;
	}
	return (size);
}
int	uinteger_array_size(int *array)
{
	int i;

	i = 0;
	if (!array)
		return (0);
	while (array[i] != -1)
		i++;
	return (i);
}

void	revert_quoted_chars(char *input)
{
	int i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = get_revert_size(input);
	if (size == 0)
		return ;
	if (g_global.quoted_flags != 0)
		free(g_global.quoted_flags);
	g_global.quoted_flags = (int *)malloc(sizeof(int) * (size + 1));
	while (input[i] != '\0')
	{
		if (input[i] == '&')
		{
			input[i] = '<';
			g_global.quoted_flags[j] = i;
			j++;
		}
		if (input[i] == '*')
		{
			input[i] = '>';
			g_global.quoted_flags[j] = i;
			j++;
		}
		if (input[i] == ';')
		{
			input[i] = '|';
			g_global.quoted_flags[j] = i;
			j++;
		}
		if (input[i] == '(')
		{
			input[i] = 34;
			g_global.quoted_flags[j] = i;
			j++;
		}
		if (input[i] == ')')
		{
			input[i] = 39;
			g_global.quoted_flags[j] = i;
			j++;
		}
		if (input[i] == '!')
		{
			input[i] = '$';
			g_global.quoted_flags[j] = i;
			j++;
		}
		i++;
	}
	g_global.quoted_flags[j] = -1;
}

void handle_input(char *input, char **envp)
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
	/*printf("\n----------\n");
	printf("%s", input);
	printf("\n----------\n");*/
	revert_quoted_chars(input);
	int	casse;
	int	is_meta;
	is_meta = detect_meta_chars(input);
	//printf("%d\n", is_meta);
	if (is_meta > 0)
	{
		do_meta_chars(input, is_meta, envp); // backslash in compleate pipes end chrashes.
		return ;
	}
	casse = detect_path_executable(input);
	//printf("case: %d\n", casse);
	if (casse > 0)
	{
		do_pathed_executable(input, casse, envp);
		return;
	}
	do_base_case(input, envp);
}
