/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:37:23 by lkukhale          #+#    #+#             */
/*   Updated: 2022/11/18 21:10:28 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_digits(int n)
{
	int	count;

	count = 0;
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

void	make_array(char *number, int n, int size)
{
	if (n < 0)
		n *= -1;
	while (size >= 0)
	{
		number[size] = 48 + (n % 10);
		n = n / 10;
		size--;
	}
}

void	min_int(char *number)
{
	number[0] = '-';
	number[1] = '2';
	number[2] = '1';
	number[3] = '4';
	number[4] = '7';
	number[5] = '4';
	number[6] = '8';
	number[7] = '3';
	number[8] = '6';
	number[9] = '4';
	number[10] = '8';
	number[11] = '\0';
}

char	*make_edge(int n)
{
	char	*number;

	if (n == 0)
	{
		number = (char *)malloc(2 * sizeof(char));
		if (!number)
			return (0);
		number[0] = 48;
		number[1] = '\0';
	}
	else
	{
		number = (char *)malloc(12 * sizeof(char));
		if (!number)
			return (0);
		min_int(number);
	}
	return (number);
}

char	*ft_itoa(int n)
{
	int		digits;
	int		sign;
	char	*number;

	if (n == -2147483647 - 1 || n == 0)
		return (make_edge(n));
	digits = get_digits(n);
	sign = 0;
	if (n < 0)
		sign = 1;
	number = (char *)malloc((digits + sign + 1) * sizeof(char));
	if (!number)
		return (0);
	make_array(number, n, (digits + sign - 1));
	number[digits + sign] = '\0';
	if (sign)
		number[0] = '-';
	return (number);
}
