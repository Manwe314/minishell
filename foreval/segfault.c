/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segfault.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:20:42 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/28 16:21:49 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int	i;
	int	*ptr;

	ptr = 0;
	*ptr = 42;
	i = 1;
	printf ("amount of arguments: %d\n", argc - 1);
	while (i < argc)
	{
		printf("arg n0 %d: %s\n", i, argv[i]);
		i++;
	}
	return (0);
}
