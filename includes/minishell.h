/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:48:55 by beaudibe          #+#    #+#             */
/*   Updated: 2023/03/20 19:46:29 by lkukhale         ###   ########.fr       */
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

# define SUCCEED 1
# define ERROR 0

char	*get_input();
void	handle_input(char *input, char **envp);
void	do_base_case(char *input, char **envp);
char	*get_command(char *name, char **paths);
char	*get_path(char **envp);
void	execute_command(char *command, char **arguments, char **envp);
void	free_split(char **split);
int		ft_pwd(void);
int		ft_cd(char *path);
int		ft_echo(char *str, int n_flag);
int		ft_export(char *name);

#endif
