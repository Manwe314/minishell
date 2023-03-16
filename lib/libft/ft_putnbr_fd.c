/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:09:54 by lkukhale          #+#    #+#             */
/*   Updated: 2022/11/15 19:30:59 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print(int i, int fd)
{
	i += '0';
	write(fd, &i, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		d;
	int		r;
	char	m;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	m = '-';
	if (n < 0)
	{
		n = n * (-1);
		write(fd, &m, 1);
	}
	d = n / 10;
	r = n % 10;
	if (d != 0)
	{
		ft_putnbr_fd(d, fd);
	}
	print(r, fd);
}
