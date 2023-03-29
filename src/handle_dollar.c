/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:03:41 by beaudibe          #+#    #+#             */
/*   Updated: 2023/03/29 16:41:41 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* ft_str_replace() replaces a string with another string
* @param str: the string to replace in
* @param to_replace: the string to replace
* @param replace_with: the string to replace with
*/

char	*ft_str_replace(char *str, char *to_replace, char *replace_with)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*new_str;
	int		i;

	i = 0;
	tmp = ft_strnstr(str, to_replace, ft_strlen(str));
	tmp2 = ft_substr(str, 0, tmp - str - 1);
	if (!replace_with)
	{
		i = 1;
		replace_with = ft_strdup("");
	}
	tmp3 = ft_strjoin(tmp2, replace_with);
	free(tmp2);
	tmp2 = ft_substr(str, tmp - str + ft_strlen(to_replace), ft_strlen(str));
	free(str);
	new_str = ft_strjoin(tmp3, tmp2);
	free(tmp2);
	free(tmp3);
	if (i)
		free(replace_with);
	return (new_str);
}

char	*ft_handle_dollar(char *str)
{
	int		i;
	int		j;
	char	*tmp;
    char    *new_str;

	i = -1;
    new_str = ft_strdup(str);
	if (!new_str || !str)
		return (NULL);
	while (new_str[++i])
	{
		if (new_str[i] == '$')
		{
			j = 0;
			i++;
			while (new_str[i + j] && ft_isalnum(new_str[i + j]))
				j++;
			tmp = ft_substr(new_str, i, j);
			new_str = ft_str_replace(new_str, tmp, getenv(tmp));
			i = -1;
			free(tmp);
		}
	}
	return (new_str);
}

