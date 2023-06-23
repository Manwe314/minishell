# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 60
# endif
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
int	ft_strlengnl(char *str);
char	*ft_strjoingnl(char *s1, char *s2);

int	ft_strchrgnl(char *s, char c)
{
	int		i;
	char	*str;
	char	c1;

	str = (char *)s;
	c1 = c;
	i = 0;
	if (!s)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c1)
			return (1);
		i++;
	}
	if (str[i] == c1)
		return (1);
	return (0);
}

char	*ft_strjoingnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (0);
	str = malloc((ft_strlengnl(s1) + ft_strlengnl(s2) + 1) * sizeof(char));
	if (str == 0)
		return (0);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[ft_strlengnl(s1) + ft_strlengnl(s2)] = '\0';
	free(s1);
	return (str);
}

int	ft_strlengnl(char *str)
{
	int	i;

	i = 0;
	if (str == 0)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

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

int main()
{
	char *line;

	line = get_next_line(0);
	printf("input ~: %s", line);
	return (0);
}