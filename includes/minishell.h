/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:48:55 by beaudibe          #+#    #+#             */
/*   Updated: 2023/03/20 16:12:06 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "stdio.h"
# include "stdlib.h"
# include "signal.h"
# include "libft.h"
# include "get_next_line_bonus.h"

# define SUCCEED 1
# define ERROR 0

int ft_cd(char *path);
int ft_pwd(void);
int ft_echo(char *str, int n_flag);
int ft_export(char *name);
int ft_export(char *str);


typedef struct s_global
{
	char **environ;
}	t_global;


extern t_global g_global;

#endif
