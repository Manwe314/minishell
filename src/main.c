/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:48:26 by beaudibe          #+#    #+#             */
/*   Updated: 2023/03/18 15:10:44 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char *ft_remove_n(char *str)
{
	if (str[ft_strlen(str) - 1] == '\n')
		str[ft_strlen(str) - 1] = '\0';
	return (str);
}

int main(int a, char **b)
{
	(void)a;
	printf("%s\n",getenv("pop"));
	ft_export(b[1]);
	printf("%s\n",getenv("pop"));
	/*while(1)
	{
		ft_putstr_fd("➜ minishell$ :",1);
		msg = ft_remove_n(get_next_line(0));
		ft_cd(msg);
		free(msg);
	}*/
	/*signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	char *b = readline()*/
	return (0);
}
