/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_overflow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:34:33 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/30 19:15:57 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd_er(void)
{
	int		i;
	char	*temp;

	i = find_pwd();
	ft_putstr_fd("cd: error retrieving current directory: ", \
	g_global.save_stdout);
	perror("getcwd");
	if (i < 0)
		return ;
	temp = ft_strjoin(g_global.environ[i], "/..");
	free(g_global.environ[i]);
	g_global.environ[i] = temp;
}
