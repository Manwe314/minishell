/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:48:55 by beaudibe          #+#    #+#             */
/*   Updated: 2023/07/04 19:41:20 by lkukhale         ###   ########.fr       */
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
# include <termios.h>
# include <unistd.h>

# define SUCCEED 1
# define ERROR 0

typedef struct s_doc
{
	char			*doc;
	int				num;
	struct s_doc	*next;

}	t_doc;

typedef struct s_global
{
	char		**environ;
	char		**history;
	char		*command;
	char		*input;
	char		*here_doc;
	int			*fds;
	int			save_stdin;
	int			save_stdout;
	int			f_pipes[2];
	int			last_out;
	int			last_in;
	int			last_write_pipe;
	int			error_status;
	int			is_piped;
	int			fd_size;
	int			exit_status;
	int			is_cat;
	int			is_heredoc;
	int			pid;
	int			hdoc;
	int			no_env;
	int			is_waiting;
	int			fsize;
	int			c_happen;
	int			stop_signal;
	pid_t		h_pid;
	t_doc		*docs;
}				t_global;
extern t_global	g_global;

void			sub_handle_heredoc_two(void);
void			sub_handle_heredoc_one(void);
int				input_handler(char *input);
int				heredoc(int pip0, int pip1, char *delim);
char			*handle_dollar(char *input);
char			*expand_variable(char *input, int i, int varibale_size);
char			*get_variable_value(char *name);
int				variable_name_size(char *input, int i);
int				has_dollar(char *input);
char			*handle_exit_status(void);
void			execution(char *command, char **arguments);
char			*set_up_piping(char *input);
void			piping(char *input);
void			pipeline(char **input, int size);
void			piped_command_middle(char *input, int *inpip, int *outpip, int i);
void			piped_command_end(char *input, int *pip, int i);
void			piped_command_start(char *input, int *pip, int i);
char			*get_clean_command(char **arguments);
void			clean_up(char **arguments, char *command, char *input);
char			**clean_up_split(char **arguments);
void			remove_quotes_from_args(char **arguments);
char			**remove_redirections(char **arguments);
char			**make_new_arguments(char **old, int size);
char			*take_command(char *input);
int				get_new_arguments_size(char **arguments);
int				has_command(char **arguments, int index);
int				is_after_redirect(char **arguments, int index);
char			**ft_split_q(char *s, char c);
void			make_strings_q(char *s, char c, char **strings);
char			*make_string_q(char *s, int i, int size);
int				word_count_q(char *s, char c);
int				word_size_q(char *s, char c, int i);
char			*remove_path(char *command);
char			*clean_command(char *command, int casse);
int				execute_command(char *command, char **arguments, char **envp);
char			*get_command(char *name, char **paths);
char			*get_path(char **envp);
int				command_start_index(char *input, int start);
int				jump_fdelim(char *input, int i);
void			do_redirections(char *input);
void			redirect(char *input, int i, int j, char *name);
int				change_fd(char *dir, char *name, int fd);
int				get_fd_size(char *input);
void			do_heredocs(char *input);
char			*get_fname_delim(char *input, int index);
char			*clean_redirection_token(char *input, int start, int end);
int				check_piping(char *input);
char			*clean_home_path(char *path, char **envp);
int				home_begin_size(char *home);
char			*return_user(char *path);
char			*get_home(char **envp);
char			*expand_home_directory(char *path, char **envp);
int				detect_path_executable(char *input);
int				*find_quote_pairs(char *input, int start);
void			handle_heredoc(char *delim);
char			*finish_piped_input(char *input);
int				initial_pipe_check(char *input);
int				is_all_space(char *input);
int				is_quoted(char *input, int index);
int				validate_input(char *input);
int				check_pipe_token(char *input, int i);
int				check_redirection_token(char *input, int i);
int				is_open_quotes(char *input);
int				error_handler(char *msg, int flag);
void			free_split(char **split);
int				split_size(char **split);
int				find_pwd(void);
char			*get_input(void);
int				ft_cd(char **path);
int				env_exist(char *str);
int				is_flaged(char *str);
int				ft_echo(char **str);
int				ft_pwd(void);
int				ft_env(void);
int				is_invalid_identifier(char a);
int				is_valid_exp(char *str, int f);
int				does_match(char *str, int v_flag);
int				match_and_validate(char **arguments, int *err);
int				get_new_env_size(char **arguments, int *err);
int				is_in_args(char **args, char *str);
char			*find_and_add(char **args, char *str);
char			*put_in_env(char *str);
char			**build_new_env(char **arguments, int size);
int				export(char **arguments);
int				ft_export_str(char **str);
int				ft_unset_str(char **str);
int				check_bounds(char *number);
int				check_char(char *number);
int				handle_exit(char **arguments);
int				ft_is_buitin(char **str);
int				ft_execute_command_builtin(char **str);
int				ft_print_env_alphabeticaly(void);
void			ft_clear_history(void);
int				ft_add_history(char *line);
void			ft_history(void);
void			ft_free_global(void);
void			ft_init_global(void);
void			ft_init_global_two(void);
void			handle_ctrl_c(int sig);
void			handle_ctrl_d(int sig);
void			handle_ctrl_backslash(int sig);
void			handle_signals(void);
int				ft_unset(char *str);
void			update_pwd(char *pwd, int flag);
char			*get_fname_delim_hdoc(char *input, int index);
char			*clean_redirection_token_hdoc(char *input, int start, int end);
void			rl_replace_line(const char *text, int clear_undo);
char			**remove_duplicates(char **arguments);
char			**refactor_arguments(char **arguments);
char			*get_variable_name(char *input);
void			update_pwd_er(void);

#endif
