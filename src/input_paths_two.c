/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_paths_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:52:17 by lkukhale          #+#    #+#             */
/*   Updated: 2023/03/24 11:10:40 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], "HOME=", 5) != 0)
		i++;
	return (envp[i] + 5);
}

char	*return_user(char *path)
{
	int		i;
	int		size;
	char	*user;

	i = 1;
	size = 0;
	while (path[i] != '/')
	{
		size++;
		i++;
	}
	user = malloc(size * sizeof(char));
	i = 1;
	while (path[i] != '/')
	{
		user[i - 1] = path[i];
		i++;
	}
	return (user);
}

int	home_begin_size(char *home)
{
	int i;

	i = ft_strlen(home) - 1;
	while (home[i] != '/')
		i--;
	return (i + 1);
}
