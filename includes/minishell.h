/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:48:55 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/16 14:58:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line_bonus.h"
# include "libft.h"
# include "signal.h"
# include "stdio.h"
# include "stdlib.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>
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
	int		last_write_pipe;
	char	*here_doc;
	char		*input;
	int			exit_status;
	int			*quoted_flags;
	int 	is_cat;
}	t_global;

extern t_global	g_global;

int env_exist(char *str);
int	ft_is_buitin(char **str);
void			handle_signals(void);
int				ft_add_history(char *line);
char			*get_input(void);
void handle_input(char *input, char **envp);
void			do_base_case(char *input, char **envp);
char			*get_command(char *name, char **paths);
char			*get_path(char **envp);
void			execute_command(char *command, char **arguments, char **envp);
int				detect_path_executable(char *input);
char			*get_home(char **envp);
char			*return_user(char *path);
int				home_begin_size(char *home);
void			do_pathed_executable(char *input, int casse, char **envp);
void			remove_path(char **arguments);
char			*expand_home_directory(char *path, char **envp);
char			*clean_home_path(char *path, char **envp);
void			free_split(char **split);
int				ft_pwd(void);
int				ft_cd(char **path);
int				ft_echo(char **str, int n_flag);
int				ft_export(char *name);
int				ft_unset(char *str);
int				ft_add_history(char *line);
void			ft_clear_history(void);
int			ft_history(void);
char			*ft_handle_dollar(char *str);
int				*find_quote_pairs(char *input, int start);
char			*make_path_one(char *input);
int				init_size_arguments_one(char *input, int *quote_pair);
void			put_in_arguments_one(char *input, char **arguments, \
					int *quote_pair);
char			**make_arguments_one(char *input, int *quote_pair);
void execute_case_one(char *input, char **envp);
int				is_begining(char *input, int index);
int				ft_execute_command_builtin(char **str);
int	ft_print_env_alphabeticaly(void);
int	ft_env(void);
int env_exist(char *str);


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

int	ft_add_history(char *line);
void ft_clear_history();
int	*find_quote_pairs(char *input, int start);
char	*make_path_one(char *input);
int	init_size_arguments_one(char *input, int *quote_pair);
void	put_in_arguments_one(char *input, char **arguments, int *quote_pair);
char	**make_arguments_one(char *input, int *quote_pair);
int	is_begining(char *input, int index);
int	get_insert_size(char *input);
char	*insert_spaces(char *input);
int	redirect_case(char **arguments, int i);
int	get_fd_size(char **arguments);
void handle_heredoc(char *delim);
void	execute_case_two(char *input);
void	close_fds(int size);
char	*set_up_execution_two(char **arguments, char *name);
int initial_pipe_check(char *input);
char *finish_piped_input(char *input);
void	piped_command_start(char *input, int *pip);
void piped_command_end(char *input, int *pip);
void piped_command_middle(char *input, int *inpip, int *outpip);
void	pipeline(char **input, int size);
void	execute_case_four(char *input);
int split_size(char **split);
int	is_all_space(char *input);
void change_quoted_char(char *input);
int	is_flaged(int index);
#endif
