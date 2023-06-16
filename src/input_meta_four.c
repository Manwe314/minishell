/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_meta_four.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:31:10 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/16 14:50:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	initial_pipe_check(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ' && input[i] != '\0')
		i++;
	if (input[i] == '|') // check quote flag
		return (-1);
	i = ft_strlengnl(input);
	i--;
	while (i >= 0 && input[i] == ' ')
		i--;
	if (input[i] == '|') // check quote flag
		return (1);
	return (0);
}

char	*finish_piped_input(char *input)
{
	char	*added_input;
	char	*temp;

	while (1)
	{
		added_input = readline("> ");
		if (is_all_space(added_input) == 0)
			if (initial_pipe_check(added_input) != 1)
				break ;
		temp = ft_strjoin(input, added_input);
		free(input);
		free(added_input);
		input = temp;
	}
	temp = ft_strjoin(input, added_input);
	free(input);
	free(added_input);
	return (temp);
}

void	piped_command_start(char *input, int *pip)
{
	if (dup2(pip[1], STDOUT_FILENO) < 0)
		perror("dup PcS:");
	g_global.last_write_pipe = dup(pip[1]);
	close(pip[0]);
	close(pip[1]);
	handle_input(input, g_global.environ);
	exit(1);
}

void	piped_command_end(char *input, int *pip)
{
	//printf("pip end: %d & %d\n", pip[0], pip[1]);
	if (dup2(pip[0], STDIN_FILENO) < 0)
		perror("dup PcE:");
	close(pip[1]);
	close(pip[0]);
	handle_input(input, g_global.environ);
	exit(1);
}

void	piped_command_middle(char *input, int *inpip, int *outpip)
{
	//printf("inpip: %d & %d\noutpip: %d & %d\n", inpip[0], inpip[1], outpip[0], outpip[1]);
	if (dup2(inpip[0], STDIN_FILENO) < 0)
		perror("dup PcM-i:");
	if (dup2(outpip[1], STDOUT_FILENO) < 0)
		perror("dup PcM-o:");

	g_global.last_write_pipe = dup(outpip[1]);
	//printf("outpip: %d\nlast pipe: %d\n", outpip[1], g_global.last_write_pipe);
	close(outpip[0]);
	close(inpip[0]);
	close(inpip[1]);
	close(outpip[1]);
	handle_input(input, g_global.environ);
	exit(1);
}