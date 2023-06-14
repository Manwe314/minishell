/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_builtin.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:13:30 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/14 20:51:18 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_invalid_identifier(char a)
{
	if (a >= 0 && a <= 47)
		return (1);
	if (a >= 58 && a <= 64)
		return (1);
	if (a >= 91 && a <= 96)
		return (1);
	if (a >= 123)
		return (1);
	return (0);
}

int sub_is_valid_exp_one(char *str, int f)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (is_invalid_identifier(str[i]) == 1)
		{
			if (f != 0)
			{
				ft_putstr_fd(str, 1);
				ft_putstr_fd(" : has an invalid identifier : ", 1);
				ft_putchar_fd(str[i], 1);
				ft_putchar_fd('\n', 1);
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int sub_is_valid_exp_two(char *str, int f)
{
	if (str[0] == '=')
	{
		if ( f != 0)
		{
			ft_putstr_fd(str, 1);
			ft_putstr_fd(" : has an invalid identifier\n", 1);
		}
		return (0);
	}
	return (1);
}

int sub_is_valid_exp_three(char *str, int f)
{
	int i;

	i = 0;
	while (str[i] != '=')
	{
		if (is_invalid_identifier(str[i]) == 1)
		{
			if (f != 0)
			{
				ft_putstr_fd(str, 1);
				ft_putstr_fd(" : has an invalid identifier : ", 1);
				ft_putchar_fd(str[i], 1);
				ft_putchar_fd('\n', 1);
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int is_valid_exp(char *str, int f)
{
	if (ft_strchr(str, '=') == 0)
	{
		if (sub_is_valid_exp_one(str, f) == 0)
			return (0);
	}
	else
	{
		if (sub_is_valid_exp_two(str, f) == 0)
			return (0);
		if (sub_is_valid_exp_three(str, f) == 0)
			return (0);
	}
	return (1);
}

int does_match(char *str, int v_flag)
{
	int i;
	int len;

	i = 0;
	if (str == 0 || v_flag == 1)
		return (0);
	while (str[i] != '=' && str[i] != '\0')
		i++;
	len = i;
	i = 0;
	while (g_global.environ[i] != 0)
	{
		if ((ft_strncmp(g_global.environ[i], str, len) == 0 ) \
		&& (g_global.environ[i][len] == '='))
			return (1);
		i++;
	}
	return (0);
}

int match_and_validate(char **arguments, int *err)
{
	int i;
	int size;
	int v_flag;

	i = 1;
	size = 0;
	v_flag = 0;
	while (arguments[i] != 0)
	{
		if (!is_valid_exp(arguments[i], 1))
		{
			*err = 1;
			size++;
			v_flag = 1;
		}
		if (does_match(arguments[i], v_flag))
			size++;
		v_flag = 0;
		i++;
	}
	return (size);
}

int get_new_env_size(char **arguments, int *err)
{
	int env_size;
	int removal_size;
	int i;

	env_size = 0;
	while (g_global.environ[env_size] != 0)
		env_size++;
	i = 0;
	while (arguments[i] != 0)
		i++;
	env_size = env_size + i;
	removal_size = match_and_validate(arguments, err);
	return (env_size - removal_size);
}

int is_in_args(char **args, char *str)
{
	int i;
	int len;

	i = 1;
	len = 0;
	while (str[len] != '=' && str[len] != '\0')
		len++;
	while (args[i] != 0)
	{
		if ((ft_strncmp(args[i], str, len) == 0) && \
		(args[i][len] == '=' || args[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

char *find_and_add(char **args, char *str)
{
	int id;
	char *new;
	char *tmp;

	id = is_in_args(args, str);
	new = ft_strdup(args[id]);
	if (ft_strchr(new, '=') == 0)
	{
		tmp = ft_strjoin(new, "=");
		free(new);
		new = tmp;
	}
	return (new);
}

char *put_in_env(char *str)
{
	char *new;
	char *tmp;

	new = ft_strdup(str);
	if (ft_strchr(new, '=') == 0)
	{
		tmp = ft_strjoin(new, "=");
		free(new);
		new = tmp;
	}
	return (new);
}

char **build_new_env(char **arguments, int size)
{
	char **new_env;
	int i;
	int j;

	new_env = (char **)malloc(size * sizeof(char *));
	i = -1;
	j = 1;
	while (g_global.environ[++i] != 0)
	{
		if (is_in_args(arguments, g_global.environ[i]) >= 0)
			new_env[i] = find_and_add(arguments, g_global.environ[i]);
		else
			new_env[i] = ft_strdup(g_global.environ[i]);
	}
	while (arguments[j] != 0)
	{
		if (is_in_args(g_global.environ, arguments[j]) == -1 \
		&& is_valid_exp(arguments[j], 0))
			new_env[i++] = put_in_env(arguments[j]);
		j++;
	}
	new_env[i] = 0;
	return (new_env);
}

int export(char **arguments)
{
	int has_error;
	char **new_env;


	has_error = 0;
	new_env = build_new_env(arguments, \
	get_new_env_size(arguments, &has_error));
	free_split(g_global.environ);
	g_global.environ = new_env;
	return (has_error);
}

int	ft_export_str(char **str)
{
	int	i;

	i = 0;
	if (!str[1])
		return (ft_print_env_alphabeticaly());
	return (export(str));
}

int	ft_unset_str(char **str)
{
	int	i;
	int	j;

	i = 0;
	if (!str[1])
		return (0);
	while (str[++i])
		j = ft_unset(str[i]);
	return (j);
}

int check_bounds(char *number)
{
	if (ft_strlengnl(number) == 10 && ft_strncmp("2147483647", number, 10) < 0)
		return (1);
	if (ft_strlengnl(number) >= 11 && number[0] != '-')
		return (1);
	if (ft_strlengnl(number) == 11 && \
	ft_strncmp("-2147483647", number, 11) < 0)
		return (1);
	if (ft_strlengnl(number) >= 12)
		return (1);
	return (0);
}

int check_char(char *number)
{
	int i;

	i = 0;
	if (number[0] == '-')
		i++;
	while (number[i] != '\0')
	{
		if (number[i] < '0' || number[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int handle_exit(char **arguments)
{
	if (split_size(arguments) > 2)
	{
		printf("exit: invalid number of arguments\n");
		return (1);
	}
	else if (arguments[1] != 0 && (check_char(arguments[1]) \
	|| check_bounds(arguments[1])))
	{
		printf("exit: %s: numeric value required\n", arguments[1]);
		g_global.error_status = 2;
		return (255);
	}
	else if (arguments[1] == 0)
	{
		g_global.error_status = 2;
		return (0);
	}
	else
	{
		g_global.error_status = 2;
		return (ft_atoi(arguments[1]) % 256);
	}
}

int	ft_is_buitin(char **str)
{
	if (ft_strncmp(str[0], "echo", 4) == 0)
		return (SUCCEED);
	else if (ft_strncmp(str[0], "cd\0", 3) == 0)
		return (SUCCEED);
	else if (ft_strncmp(str[0], "pwd\0", 4) == 0)
		return (SUCCEED);
	else if (ft_strncmp(str[0], "export\0", 7) == 0)
		return (SUCCEED);
	else if (ft_strncmp(str[0], "unset\0", 6) == 0)
		return (SUCCEED);
	else if (ft_strncmp(str[0], "env\0", 4) == 0)
		return (SUCCEED);
	else if (ft_strncmp(str[0], "history\0", 8) == 0)
		return (SUCCEED);
	else if (ft_strncmp(str[0], "exit\0", 5) == 0)
		return (SUCCEED);
	return (ERROR);
}

int	ft_execute_command_builtin(char **str)
{
	if (ft_strncmp(str[0], "echo", 4) == 0)
		return (ft_echo(str));
	else if (ft_strncmp(str[0], "cd", 2) == 0)
		return (ft_cd(str));
	else if (ft_strncmp(str[0], "pwd", 3) == 0)
		return (ft_pwd());
	else if (ft_strncmp(str[0], "export", 6) == 0)
		return (ft_export_str(str));
	else if (ft_strncmp(str[0], "unset", 5) == 0)
		return (ft_unset_str(str));
	else if (ft_strncmp(str[0], "env", 3) == 0)
		return (ft_env());
	else if (ft_strncmp(str[0], "history", 7) == 0)
	{
		ft_history();
		return (0);
	}
	else if (ft_strncmp(str[0], "exit\0", 5) == 0)
		return (handle_exit(str));
	return (-1);
}