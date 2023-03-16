/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:41:58 by lkukhale          #+#    #+#             */
/*   Updated: 2023/03/16 19:07:23 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*save_the_state(char *current)
{
	int		i;
	int		j;
	char	*new_state;

	i = 0;
	while (current[i] != '\0' && current[i] != '\n')
		i++;
	if (!current[i])
	{
		free(current);
		return (0);
	}
	new_state = malloc(sizeof(char) * ft_strlengnl(current) - i + 1);
	if (!new_state)
		return (0);
	i++;
	j = 0;
	while (current[i] != '\0')
		new_state[j++] = current[i++];
	new_state[j] = '\0';
	free(current);
	return (new_state);
}

char	*give_the_line(char *current)
{
	int		i;
	char	*line;

	i = 0;
	if (!current[i])
		return (0);
	while (current[i] != '\0' && current[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (0);
	i = 0;
	while (current[i] != '\0' && current[i] != '\n')
	{
		line[i] = current[i];
		i++;
	}
	if (current[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*read_line(char *save, int fd)
{
	char	*buffer;
	int		read_status;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (0);
	read_status = 1;
	while (!ft_strchrgnl(save, '\n') && read_status != 0)
	{
		read_status = read(fd, buffer, BUFFER_SIZE);
		if (read_status == -1)
		{
			free(buffer);
			return (0);
		}
		buffer[read_status] = '\0';
		save = ft_strjoingnl(save, buffer);
	}
	free(buffer);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save_state[1025];
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	save_state[fd] = read_line(save_state[fd], fd);
	if (!save_state[fd])
		return (0);
	next_line = give_the_line(save_state[fd]);
	save_state[fd] = save_the_state(save_state[fd]);
	return (next_line);
}
