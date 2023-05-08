# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

int main(int argc, char *argv[], char **envp)
{
	int i = 0;
	(void)argc;
	int save;
	pid_t id;
	char path[30] = "/usr/bin/wc";
	char *arg[3];
	int	pip[2];

	arg[0] = "wc";
	arg[1] = "lol";
	arg[2] = 0;
	pipe(pip);
	save = dup(STDIN_FILENO);
	if (argc <= 1)
		return (0);
	dup2(pip[0], STDIN_FILENO);
	while (argv[1][i] != '\0')
	{
		write(pip[1], &argv[1][i], 1);
		i++;
	}
	write(pip[1], "\n", 1);
	close(pip[1]);
	id = fork();
	if (id == 0)
	{
		execve(path, arg, envp);
	}
	waitpid(id, 0, 0);
	write(save, "hey\n", 4);
	return (0);

}