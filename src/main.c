/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:48:26 by beaudibe          #+#    #+#             */
/*   Updated: 2023/03/24 10:39:51 by beaudibe         ###   ########.fr       */
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

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	char* input;
	/*printf("%s\n",getenv("pop"));
	ft_export(argv[1]);
	printf("%s\n",getenv("pop"));*/
	while(1)
	{
		input = get_input();
		if (input == NULL)
			break ;
		handle_input(input, envp);
		//ft_cd(msg);
		//free(msg);
	}
	ft_putchar_fd('\n', 1);
	/*signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	char *argv = readline()*/
	ft_free_global();
	return (0);
}
