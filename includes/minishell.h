/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:48:55 by beaudibe          #+#    #+#             */
/*   Updated: 2023/04/25 15:51:42 by beaudibe         ###   ########.fr       */
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


# define SUCCEED 1
# define ERROR 0

typedef struct s_global
{
	char	**environ;
	char	**history;
	int		exit_status;
	int		ctrl_c;
	char *input;
}	t_global;
extern t_global g_global;

void handle_signals();
int	ft_add_history(char *line);
char	*get_input();
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
char *ft_handle_dollar(char *str);


#endif
