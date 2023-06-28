/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitingtwo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:27:14 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/28 16:29:06 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 60
#endif

char	*give_the_line(char *current);
char	*save_the_state(char *current);
int		ft_strlengnl(char *str);
char	*ft_strjoingnl(char *s1, char *s2);
int		ft_strchrgnl(char *s, char c);

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

int	main(void)
{
	char	*line;

	line = get_next_line(0);
	printf("input ~: %s", line);
	return (0);
}
