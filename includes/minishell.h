/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:48:55 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/08 21:33:24 by lkukhale         ###   ########.fr       */
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
	int		last_write_pipe;
	int		error_status;
	int		quoted_flags;
	int		is_piped;
	int		fd_size;
	int 	exit_status;
	char 	*input;
	char	*here_doc;
}	t_global;
extern t_global g_global;

int	ft_env(void);
int	ft_pwd(void);
int	ft_echo(char **str, int n_flag);
int	ft_cd(char **path);

int	ft_print_env_alphabeticaly(void);
int	ft_change_env(char *name, char *value);
int	ft_add_env(char *name, char *value);
int	ft_export(char *str);

char	*ft_strjoingnl(char *s1, char *s2);
int	ft_strlengnl(char *str);
int	ft_strchrgnl(char *s, char c);
char	*get_next_line(int fd);

void	ft_history(void);
int	ft_add_history(char *line);
void	ft_clear_history(void);

void	handle_signals(void);
void	handle_ctrl_backslash(int sig);
void	handle_ctrl_d(int sig);
void	handle_ctrl_c(int sig);

int ft_unset(char *str);
int	ft_unset_str(char **str);
int	ft_export_str(char **str);
int	ft_is_buitin(char **str);
int	ft_execute_command_builtin(char **str);

char *get_input();
int split_size(char **split);
void	free_split(char **split);
int error_handler(char *msg, int flag);
int	is_open_quotes(char *input);
int check_redirection_token(char *input, int i);
int check_pipe_token(char *input, int i);
int	validate_input(char *input);
int is_quoted(char *input, int index);
int	is_all_space(char *input);
int initial_pipe_check(char *input);
char *finish_piped_input(char *input);
void handle_heredoc(char *delim);
int	*find_quote_pairs(char *input, int start);
int	detect_path_executable(char *input);
char	*expand_home_directory(char *path, char **envp);
char	*get_home(char **envp);
char	*return_user(char *path);
int	home_begin_size(char *home);
char	*clean_home_path(char *path, char **envp);
char *clean_redirection_token(char *input, int start, int end);
char *get_fname_delim(char *input, int index);
void	do_heredocs(char *input);
int	change_fd(char *input, int i, char *name, int fd);
int	get_fd_size(char *input);
void redirect(char *input);
void do_redirections(char *input);
int jump_fdelim(char *input, int i);
int	command_start_index(char *input, int start);
char	*get_path(char **envp);
char	*get_command(char *name, char **paths);
void execute_command(char *command, char **arguments, char **envp);
char *clean_command(char *command, int casse);
char *remove_path(char *command);
int	word_size_q(char *s, char c, int i);
int	word_count_q(char *s, char c);
char	*make_string_q(char *s, int i, int size);
void	make_strings_q(char *s, char c, char **strings);
char	**ft_split_q(char *s, char c);
int is_after_redirect(char **arguments, int index);
int has_command(char **arguments, int index);
int get_new_arguments_size(char **arguments);
char *take_command(char *input);
void make_new_arguments(char **new, char **old);
char **remove_redirections(char **arguments);
void remove_quotes_from_args(char **arguments);
char **clean_up_split(char **arguments);
void clean_up(char **arguments, char *command);
char *get_clean_command(char **arguments);
void	piped_command_start(char *input, int *pip);
void piped_command_end(char *input, int *pip);
void piped_command_middle(char *input, int *inpip, int *outpip);
void	pipeline(char **input, int size);
void	piping(char *input);
char *set_up_piping(char *input);
int input_handler(char *input);
char *handle_dollar(char *input);





#endif
