/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:48:55 by beaudibe          #+#    #+#             */
/*   Updated: 2023/05/05 18:14:37 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "stdio.h"
# include "stdlib.h"
# include "signal.h"
# include "libft.h"
# include "get_next_line_bonus.h"

# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>


# define SUCCEED 1
# define ERROR 0

typedef struct s_global
{
	char	**environ;
	char	**history;
	int		save_STDIN;
	int		save_STDOUT;
	int		*fds;
	int		f_pipes[2];
	int		last_out;
	int		last_in;
	char	*here_doc;
}	t_global;
extern t_global g_global;

void handle_signals();
int	ft_add_history(char *line);
char	 *get_input();
void	handle_input(char *input, char **envp);
void	do_base_case(char *input, char **envp);
char	*get_command(char *name, char **paths);
char	*get_path(char **envp);
void	execute_command(char *command, char **arguments, char **envp);
int		detect_path_executable(char *input);
char	*get_home(char **envp);
char	*return_user(char *path);
int		home_begin_size(char *home);
void	do_pathed_executable(char *input, int casse, char **envp);
void	remove_path(char **arguments);
char	*expand_home_directory(char *path, char **envp);
char	*clean_home_path(char *path, char **envp);
void	free_split(char **split);
int		ft_pwd(void);
int		ft_cd(char *path);
int		ft_echo(char *str, int n_flag);
int		ft_export(char *name);
int		ft_unset(char *str);
int	ft_add_history(char *line);
void ft_clear_history();
void ft_history();
int	*find_quote_pairs(char *input, int start);
char	*make_path_one(char *input);
int	init_size_arguments_one(char *input, int *quote_pair);
void	put_in_arguments_one(char *input, char **arguments, int *quote_pair);
char	**make_arguments_one(char *input, int *quote_pair);
void	execute_case_one(char *input);
int	is_begining(char *input, int index);
int	get_insert_size(char *input);
char	*insert_spaces(char *input);
int	redirect_case(char **arguments, int i);
int	get_fd_size(char **arguments);
void handle_heredoc(char *delim);
void	execute_case_two(char *input);
void	close_fds(int size);
char	*set_up_execution_two(char **arguments);
#endif
