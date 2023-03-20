/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:48:26 by beaudibe          #+#    #+#             */
/*   Updated: 2023/03/20 18:05:10 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *ft_remove_n(char *str)
{
	if (str[ft_strlen(str) - 1] == '\n')
		str[ft_strlen(str) - 1] = '\0';
	return (str);
}

void	ft_free_global()
{
	int i;

	i = -1;
	while (g_global.environ[++i])
	{
		free(g_global.environ[i]);
	}
	free(g_global.environ);
}

void ft_init_global()
{
	int i;
	extern char **environ;

	i = 0;
	while (environ[i])
		i++;
	g_global.environ = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (environ[++i]){
		g_global.environ[i] = ft_strdup(environ[i]);
	}
	g_global.environ[i] = NULL;
}


int main(int a, char **b)
{
	(void)a;
	ft_init_global();
	ft_export(b[1]);
	ft_export(0);

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
	ft_free_global();
	return (0);
}
