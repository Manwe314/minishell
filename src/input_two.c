/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:54:42 by lkukhale          #+#    #+#             */
/*   Updated: 2023/05/25 20:09:13 by lkukhale         ###   ########.fr       */
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

int split_size(char **split)
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
	while (split[i] != 0)
	{
		free(split[i]);
		i++;
	}
	free(split[i]);
	free(split);
}

int error_handler(char *msg, int flag)
{
	if (flag == 0)
	{
		if (msg != 0)
			printf("%s\n", msg);
		if (g_global.is_piped != 1)
			free(g_global.input);
		return (g_global.exit_status);
	}
	if (flag == 1)
	{
		perror(msg);
		g_global.error_status = 1;
		return (0);
	}
	if (flag == 2)
	{
		perror(msg);
		ft_putstr_fd("Fatal Error\n", g_global.save_STDOUT);
		g_global.error_status = 2;
		return (-1);
	}
	return (0);
}

int	is_open_quotes(char *input)
{
	int *quote_pair;

	quote_pair = find_quote_pairs(input, 0);
	if (quote_pair[0] != 0 && quote_pair[1] == 0)
		return (1);
	while (quote_pair[0] != 0 && quote_pair[1] != 0)
	{
		quote_pair = find_quote_pairs(input, quote_pair[1] + 1);
		if (quote_pair[0] != 0 && quote_pair[1] == 0)
			return (1);
	}
	return (0);
}

int check_redirection_token(char *input, int i)
{
	int save;

	save = i + 1;
	if (input[i] == '>')
	{
		i++;
		while (input[i] != '\0' && input[i] == ' ')
			i++;
		if (input[i] == '<' || input[i] == '\0')
			return (1);
		if (input[i] == '>' && i == save)
		{
			i++;
			while (input[i] != '\0' && input[i] == ' ')
				i++;
			if (input[i] == '<' || input[i] == '\0' || input[i] == '>')
				return (1);
		}
		else if (input[i] == '>' && i != save)
			return (1);
	}
	else if (input[i] == '<')
	{
		i++;
		while (input[i] != '\0' && input[i] == ' ')
			i++;
		if (input[i] == '>' || input[i] == '\0')
			return (1);
		if (input[i] == '<' && i == save)
		{
			i++;
			while (input[i] != '\0' && input[i] == ' ')
				i++;
			if (input[i] == '<' || input[i] == '\0' || input[i] == '>')
				return (1);
		}
		else if (input[i] == '<' && i != save)
			return (1);
	}
	return(0);
}

int check_pipe_token(char *input, int i)
{
	i++;
	while (input[i] != '\0' && input[i] == ' ')
		i++;
	if (input[i] == '|')
		return (1);
	if (initial_pipe_check(input) == -1)
		return (1);
	return (0);
}

int	validate_input(char *input)
{
	int i;
	int *quote_pair;

	i = 0;
	if (is_open_quotes(input))
		return (0);

	quote_pair = find_quote_pairs(input, 0);
	while (input[i] != '\0')
	{
		if (i == quote_pair[0] && quote_pair[1] != 0)
		{
			i = quote_pair[1];
			quote_pair = find_quote_pairs(input, quote_pair[1] + 1);
		}
		if (input[i] == '<' || input[i] == '>')
			if (check_redirection_token(input, i))
				return (0);
		if (input[i] == '|')
			if (check_pipe_token(input, i))
				return (0);
		i++;
	}
	return (1);
}

int is_quoted(char *input, int index)
{
	int *quote_pairs;

	quote_pairs = find_quote_pairs(input, 0);
	if (quote_pairs[1] == 0)
		return (0);
	while (quote_pairs[1] != 0)
	{
		if (index > quote_pairs[0] && index < quote_pairs[1])
			return (1);
		quote_pairs = find_quote_pairs(input, quote_pairs[1] + 1);
	}
	return (0);
}

int	is_all_space(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		if (input[i] == ' ' || input[i] == '	')
			j++;
		i++;
	}
	if (i == j)
		return (1);
	return (0);
}

int initial_pipe_check(char *input)
{
	int i;

	i = 0;
	while (input[i] == ' ' && input[i] != '\0')
		i++;
	if (input[i] == '|')
		return (-1);
	i = ft_strlengnl(input);
	i--;
	while (i >= 0 && input[i] == ' ')
		i--;
	if (input[i] == '|')
		return (1);
	return (0);
}

char *finish_piped_input(char *input)
{
	char *added_input;
	char *temp;

	while (1)
	{
		added_input = readline("> ");
		if (is_all_space(added_input) == 0)
			if (initial_pipe_check(added_input) != 1)
				break ;
		temp = ft_strjoin(input, added_input);
		free (input);
		free(added_input);
		input = temp;
	}
	temp = ft_strjoin(input, added_input);
	//free(input);
	free(added_input);
	return (temp);
}

void handle_heredoc(char *delim)
{
	char *input;
	char *temp;

	if (g_global.here_doc != 0)
	{
		free(g_global.here_doc);
		g_global.here_doc = 0;
	}
	if (dup2(g_global.save_STDIN, STDIN_FILENO) < 0)
		error_handler("here_doc", 2);
	if (dup2(g_global.save_STDOUT, STDOUT_FILENO) < 0)
		error_handler("here_doc", 2);
	while (1)
	{
		input = readline("> ");
		if ((ft_strncmp(delim, input, (unsigned int)ft_strlengnl(delim)) == 0 && ft_strlen(delim) == ft_strlen(input)) || input == NULL)
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
			error_handler("dup2 last out", 1);
		g_global.last_out = -1;
	}
	free(delim);
}

int	*find_quote_pairs(char *input, int start)
{
	int	i;
	int j;
	static int	quote_pair[2];

	i = start;
	quote_pair[0] = 0;
	quote_pair[1] = 0;
	while (input[i] != '\0')
	{
		if (input[i] == 39 || input[i] == 34)
		{
			j = i + 1;
			quote_pair[0] = i;
			while (input[j] != '\0' && input[i] != '\0')
			{
				if (input[j] == input[i])
				{
					quote_pair[1] = j;
					return (quote_pair);
				}
				j++;
			}
		}
		i++;
	}
	return (quote_pair);
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

char	*expand_home_directory(char *path, char **envp)
{
	char	*home;
	char	*new_path;


	home = get_home(envp);
	new_path = ft_strdup(path + 1);
	new_path = ft_strjoin(home, new_path);
	free(home);
	return (new_path);
}

char	*get_home(char **envp)
{
	int	i;
	char	*home;

	i = 0;
	while (ft_strncmp(envp[i], "HOME=", 5) != 0)
		i++;
	home = ft_strdup(envp[i] + 5);
	return (home);
}

char	*return_user(char *path)
{
	int		i;
	int		size;
	char	*user;

	i = 1;
	size = 0;
	while (path[i] != '/')
	{
		size++;
		i++;
	}
	user = malloc(size * sizeof(char));
	i = 1;
	while (path[i] != '/')
	{
		user[i - 1] = path[i];
		i++;
	}
	return (user);
}

int	home_begin_size(char *home)
{
	int i;

	i = ft_strlen(home) - 1;
	while (home[i] != '/')
		i--;
	return (i + 1);
}

char	*clean_home_path(char *path, char **envp)
{
	char	*home;
	char	*user;
	char	*new_path;
	int		sub_size;


	home = get_home(envp);
	user = return_user(path);
	sub_size = home_begin_size(home);
	home = ft_substr(home, 0, sub_size);
	new_path = ft_strjoin(home, user);
	sub_size = 0;
	while (path[sub_size] != '/')
		sub_size++;
	new_path = ft_strjoin(new_path, (path + sub_size));
	free(user);
	free(home);
	return (new_path);
}

int check_piping(char *input)
{
	int i;
	int is_piped;

	i = 0;
	is_piped = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '|' && !is_quoted(input, i))
		{
			is_piped = 1;
			break ;
		}
		i++;
	}
	return (is_piped);
}

char *clean_redirection_token(char *input, int start, int end)
{
	int i;
	int j;
	int *q_pair;
	char *token;

	q_pair = find_quote_pairs(input, start);
	i = start;
	j = start;
	token = 0;
	while (i != end)
	{
		while (i != q_pair[0] && i != end)
			i++;
		if (i == q_pair[0])
		{
			if (i != j)
				token = ft_strjoingnl(token, ft_substr(input, j, i - j));
			token = ft_strjoingnl(token, ft_substr(input, q_pair[0] + 1, q_pair[1] - q_pair[0] - 1));
			i = q_pair[1] + 1;
			j = i;
			q_pair = find_quote_pairs(input, i);
		}
		else
			token = ft_strjoingnl(token, ft_substr(input, j, i - j));
		if (i != end)
			i++;
	}
	return (token);
}

char *get_fname_delim(char *input, int index)
{
	int i;
	int	j;
	char *fdelim;
	int *q_pair;

	i = index + 1;
	q_pair = find_quote_pairs(input, index);
	while (input[i] == ' ')
		i++;
	j = i;
	while (input[i] != ' ' && input[i] != '\0' && input[i] != '<' && input[i] != '>')
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

void	do_heredocs(char *input)
{
	int i;
	char *delim;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '<' && !is_quoted(input, i))
			if (input[i + 1] == '<')
			{
				delim = get_fname_delim(input, i + 1);
				if (delim != 0)
					handle_heredoc(delim);
			}
		i++;
	}
}

int	get_fd_size(char *input)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '>' && !is_quoted(input, i))
		{
			if (input[i + 1] == '>')
				i++;
			size++;
		}
		if (input[i] == '<' && !is_quoted(input, i))
		{
			if (input[i + 1] == '<')
				i++;
			else
				size++;
		}
		i++;
	}
	return (size);
}

int	change_fd(char *input, int i, char *name, int fd)
{
	if (i != 0 && input[i] == '>' && input[i - 1] != '>')
	{
		g_global.fds[fd] = open(name, O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (g_global.fds[fd] < 0)
			return (-1);
		if (dup2(g_global.fds[fd], STDOUT_FILENO) < 0)
			error_handler("Redirection dup2", 1);
	}
	if (i != 0 && input[i] == '>' && input[i - 1] == '>')
	{
		g_global.fds[fd] = open(name, O_APPEND | O_CREAT | O_RDWR, 0644);
		if (g_global.fds[fd] < 0)
			return (-1);
		if (dup2(g_global.fds[fd], STDOUT_FILENO) < 0)
			error_handler("Redirection dup2", 1);
	}
	if (input[i] == '<')
	{
		g_global.fds[fd] = open(name, O_RDONLY);
		if (g_global.fds[fd] < 0)
			return (-1);
		if (dup2(g_global.fds[fd], STDIN_FILENO) < 0)
			error_handler("Redirection dup2", 1);
	}
	return (++g_global.fd_size);
}

void redirect(char *input)
{
	int i;
	int	j;
	char *name;

	i = 0;
	j = -1;
	name = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '<' && !is_quoted(input, i))
		{
			if (input[i + 1] == '<')
			{
				g_global.last_in = 1;
				i++;
			}
			else
			{
				g_global.last_in = -1;
				name = get_fname_delim(input, i);
				if (change_fd(input, i, name, ++j) < 0)
				{
					error_handler("infile",1);
					free(name);
					return ;
				}
			}
		}
		if (input[i] == '>' && !is_quoted(input, i))
		{
			if (input[i + 1] == '>')
			{
				i++;
				name = get_fname_delim(input, i);
				if (change_fd(input, i, name, ++j) < 0)
				{
					error_handler("outfile",1);
					free(name);
					return ;
				}
				g_global.last_out = j;
			}
			else
			{
				name = get_fname_delim(input, i);
				if (change_fd(input, i, name, ++j) < 0)
				{
					error_handler("outfile",1);
					free(name);
					return ;
				}
				g_global.last_out = j;
			}
		}
		if (input[i] != '\0')
			i++;
	}
}

void do_redirections(char *input)
{
	int size;

	if (g_global.is_piped == 0)
		do_heredocs(input);
	size = get_fd_size(input);
	g_global.fds = malloc(sizeof(int) * size);
	redirect(input);
	if (g_global.last_in == 1)
	{
		if (pipe(g_global.f_pipes) < 0)
			error_handler("here_doc", 1);
		if (dup2(g_global.f_pipes[0], STDIN_FILENO) < 0)
			error_handler("here_doc dup2", 1);
		ft_putstr_fd(g_global.here_doc, g_global.f_pipes[1]);
		close(g_global.f_pipes[1]);
		g_global.f_pipes[1] = -1;
	}
}

int jump_fdelim(char *input, int i)
{
	int *q_pair;

	q_pair = find_quote_pairs(input, i);
	while (input[i] == ' ' || input[i] == '<' || input[i] == '>')
		i++;
	while (input[i] != ' ' && input[i] != '\0' && input[i] != '<' && input[i] != '>')
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

int	command_start_index(char *input, int start)
{
	int i;

	i = start;
	while ((input[i] == ' ' || input[i] == '<' || input[i] == '>') && input[i] != '\0')
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
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	return (envp[i] + 5);
}

char	*get_command(char *name, char **paths)
{
	char	*temp;
	char	*command;
	int		i;

	i = 0;
	while (paths[i] != 0)
	{
		temp = ft_strjoin(paths[i], "/");
		command = ft_strjoin(temp, name);
		free (temp);
		if (access(command, 0) == 0)
			return (command);
		free (command);
		i++;
	}
	return (0);
}

void execute_command(char *command, char **arguments, char **envp)
{
	pid_t	executable_to_be_done;
	int		execve_return;

	/*printf("Command: %s\n", command);
	int i = 0;
	while (arguments[i])
	{
		printf("Argument[%d]: %s\n", i, arguments[i]);
		i++;
	}*/
	if (g_global.last_write_pipe != -1)
	{
		if (dup2(g_global.last_write_pipe, STDOUT_FILENO) < 0)
			perror("dup2 excve:");
		close(g_global.last_write_pipe);
	}
	execve_return = 1;
	executable_to_be_done = fork();
	if (executable_to_be_done == 0){
		execve_return = execve(command, arguments, envp);
	}
	if (execve_return == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	waitpid(executable_to_be_done, NULL, 0);
}

char *clean_command(char *command, int casse)
{
	char *path;

	if (casse == 1)
	{
		path = ft_strdup(command);
		free(command);
	}
	if (casse == 2)
	{
		path = expand_home_directory(command, g_global.environ);
		free(command);
	}
	if (casse == 3)
		path = clean_home_path(command, g_global.environ);
	if (casse == 0)
	{
		path = get_command(command, ft_split(get_path(g_global.environ), ':'));
		free(command);
	}
	return (path);
}

char *remove_path(char *command)
{

	int	i;
	int is_slash;
	char *name;

	i = 0;
	is_slash = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '/')
			is_slash = 1;
		i++;
	}
	if (!is_slash)
		return (ft_strdup(command));
	while (command[i] != '/')
		i--;
	i++;
	name = ft_substr(command, i, ft_strlen(command) - i);
	return (name);
}

int	word_size_q(char *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && !is_quoted(s, i))
			break ;
		size++;
		i++;
	}
	return (size);
}

int	word_count_q(char *s, char c)
{
	int	i;
	int	count;
	int	size;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			size = word_size_q(s, c, i);
			count++;
			i += size;
		}
		if (s[i] != '\0')
			i++;
	}
	return (count);
}

char	*make_string_q(char *s, int i, int size)
{
	char	*ptr;
	int		j;

	ptr = (char *)malloc(sizeof(char) * (size + 1));
	if (!ptr)
		return (0);
	j = 0;
	while (j < size)
	{
		ptr[j] = s[i + j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

void	make_strings_q(char *s, char c, char **strings)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			size = word_size_q(s, c, i);
			strings[j] = make_string_q(s, i, size);
			j++;
			i += size;
		}
		if (s[i] != '\0')
			i++;
	}
	strings[j] = 0;
}

char	**ft_split_q(char *s, char c)
{
	char	**strings;
	int		words;

	if (!s)
		return (0);
	words = word_count_q(s, c);
	strings = (char **)malloc((words + 1) * sizeof(char *));
	if (!strings)
		return (0);
	make_strings_q(s, c, strings);
	return (strings);
}

int is_after_redirect(char **arguments, int index)
{
	int i;

	if (index == 0)
		return (0);
	i = ft_strlen(arguments[index - 1]);
	i--;
	if (arguments[index - 1][i] == '>' || arguments[index - 1][i] == '<')
		return (1);
	return (0);
}

int has_command(char **arguments, int index)
{
	int i;

	i = 0;
	while (arguments[index][i] != '\0')
	{
		if ((arguments[index][i] == '<' || arguments[index][i] == '>') && !is_quoted(arguments[index], i))
			break ;
		i++;
	}
	if (i == 0)
		return (0);
	else
		return (1);

}

int get_new_arguments_size(char **arguments)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (arguments[i] != 0)
	{
		if (i != 0 && is_after_redirect(arguments, i))
			i++;
		if (arguments[i] == 0)
			break ;
		if (has_command(arguments, i))
			size++;
		i++;
	}
	return (size);
}

char *take_command(char *input)
{
	int i;

	i = 0;
	while (input[i] != '\0')
	{
		if ((input[i] == '<' || input[i] == '>') && !is_quoted(input, i))
			break ;
		i++;
	}
	return (ft_substr(input, 0, i));
}

void make_new_arguments(char **new, char **old)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (old[i] != 0)
	{
		if (i != 0 && is_after_redirect(old, i))
			i++;
		if (old[i] == 0)
			break ;
		if (has_command(old, i))
		{
			new[j] = take_command(old[i]);
			j++;
		}
		i++;
	}
	new[j] = 0;
}

char **remove_redirections(char **arguments)
{
	int size;
	char **new_arguments;

	size = get_new_arguments_size(arguments);
	new_arguments = (char **)malloc(sizeof(char *) * (size + 1));
	make_new_arguments(new_arguments, arguments);
	return (new_arguments);
}

void remove_quotes_from_args(char **arguments)
{
	int i;
	int *q_pair;
	char *temp;

	i = 0;
	temp = 0;
	while (arguments[i] != 0)
	{
		q_pair = find_quote_pairs(arguments[i], 0);
		if (q_pair[1] != 0)
		{
			temp = clean_redirection_token(arguments[i], 0, ft_strlengnl(arguments[i]));
			free(arguments[i]);
			arguments[i] = temp;
		}
		i++;
	}
}

char **clean_up_split(char **arguments)
{
	char **new_arguments;

	new_arguments = remove_redirections(arguments);
	remove_quotes_from_args(new_arguments);
	free_split(arguments);
	return (new_arguments);
}

void clean_up(char **arguments)
{
	int i;

	if (arguments != 0)
		free_split(arguments);
	i = 0;
	while (i < g_global.fd_size)
	{
		close(g_global.fds[i]);
		i++;
	}
	g_global.fd_size = 0;
	if (dup2(g_global.save_STDIN, STDIN_FILENO) < 0)
		error_handler("dup2 clean", 2);
	if (dup2(g_global.save_STDOUT, STDOUT_FILENO) < 0)
		error_handler("dup2 clean", 2);
	g_global.is_piped = 0;
	if (g_global.here_doc != 0)
	{
		free(g_global.here_doc);
		g_global.here_doc = 0;
	}
	g_global.last_in = 0;
	g_global.last_out = -1;
}

char *get_clean_command(char **arguments)
{
	char *command;

	if (arguments[0] != 0)
	{
		command = ft_strdup(arguments[0]);
		arguments[0] = remove_path(arguments[0]);
		command = clean_command(command, detect_path_executable(command));
	}
	else
		command = 0;
	return (command);
}

void	piped_command_start(char *input, int *pip)
{
	if (dup2(pip[1], STDOUT_FILENO) < 0)
		error_handler("dup PcS:", 1);
	g_global.last_write_pipe = dup(pip[1]);
	close(pip[0]);
	close(pip[1]);
	input_handler(input);
	exit(1);
}

void piped_command_end(char *input, int *pip)
{
	if (dup2(pip[0], STDIN_FILENO) < 0)
		error_handler("dup PcE:", 1);
	close(pip[1]);
	close(pip[0]);
	input_handler(input);
	exit(1);
}

void piped_command_middle(char *input, int *inpip, int *outpip)
{
	if (dup2(inpip[0], STDIN_FILENO) < 0)
		error_handler("dup PcM-i:", 1);
	if (dup2(outpip[1], STDOUT_FILENO) < 0)
		error_handler("dup PcM-o:", 1);
	g_global.last_write_pipe = dup(outpip[1]);
	close(outpip[0]);
	close(inpip[0]);
	close(inpip[1]);
	close(outpip[1]);
	input_handler(input);
	exit(1);
}

void	pipeline(char **input, int size)
{
	pid_t	*pids;
	int	i;
	int	**pipes;

	pids = (pid_t *)malloc(sizeof(pid_t) * size);
	pipes = (int **)malloc(sizeof(int *) * (size - 1));
	i = 0;
	while (input[i] != 0)
	{
		if (i < size - 1)
		{
			pipes[i] = (int *)malloc(sizeof(int) * 2);
			if (pipe(pipes[i]) < 0)
				error_handler("Pipe", 1);
		}
		do_heredocs(input[i]);
		pids[i] = fork();
		if (pids[i] < 0)
			error_handler("Fork", 1);
		if (i == 0 && pids[i] == 0)
			piped_command_start(input[i], pipes[0]);
		if (i != 0 && i != size - 1 && pids[i] == 0)
			piped_command_middle(input[i], pipes[i - 1], pipes[i]);
		if (i == size - 1 && pids[i] == 0)
			piped_command_end(input[i], pipes[size - 2]);
		if (i < size - 1)
			close(pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < size)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	i = 0;
	while (i < size - 1)
	{
		close(pipes[i][0]);
		free(pipes[i]);
		i++;
	}
	g_global.last_write_pipe = -1;
	free(pids);
	free(pipes);
}

void	piping(char *input)
{
	int size;
	char **pipe_split;

	// input = ft_handle_dollar(input);
	pipe_split = ft_split_q(input, '|');
	size = split_size(pipe_split);
	g_global.is_piped = 1;
	pipeline(pipe_split, size);
	free_split(pipe_split);
}

char *set_up_piping(char *input)
{
	char *temp;

	if (initial_pipe_check(input) == 1)
	{
		temp = finish_piped_input(input);
		if (!validate_input(temp))
		{
			free(temp);
			free(input);
			return (0);
		}
		else
		{
			free(input);
			return (temp);
		}
	}
	else
		return (input);
}

int input_handler(char *input)
{
	char **arguments;
	char *command;

	if (!validate_input(input))
		return (error_handler("invalid input", 0));
	if (check_piping(input))
	{
		input = set_up_piping(input);
		if (input != 0)
			piping(input);
		clean_up(0);
		return (0);
	}
	// input = ft_handle_dollar(input);
	do_redirections(input);
	if (g_global.error_status > 0)
		return (error_handler(0, 0));
	arguments = ft_split_q(input, ' ');
	arguments = clean_up_split(arguments);
	command = get_clean_command(arguments); // free command. but its not freeable if there is NO command
	/*int i = 0;
	printf("CMD: %s\n", arguments[0]);
	while (arguments[i] != 0)
	{
		printf("arg[%d]: %s\n", i, arguments[i]);
		i++;
	}*/
	if (command != 0)
		execute_command(command, arguments, g_global.environ);
	clean_up(arguments);
	return 0;
}