/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:38:02 by lkukhale          #+#    #+#             */
/*   Updated: 2023/03/16 19:07:23 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
int		ft_strchrgnl(char *s, char c);
char	*ft_strjoingnl(char *s1, char *s2);
int		ft_strlengnl(char *str);
#endif