# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 19:53:49 by lkukhale          #+#    #+#              #
#    Updated: 2023/06/15 22:01:30 by lkukhale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell
USER		= lkukhale
SRCS 		= ${shell find ./src -iname "*.c"}

HEADERS		= -I ./includes/
LIBS		= ${LIBFT}/libft.a
LIBFT		= ./lib/libft
CFLAGS		= -Wall -Wextra -Werror -g
OBJS		= ${SRCS:.c=.o}
RM			= rm -f


all:	libft	${NAME}

libft:
		make -C ${LIBFT}

.c.o:
		@${CC} ${CFLAGS} -o $@ -c $< ${HEADERS}

${NAME}:	${OBJS}
		@${CC} ${OBJS} ${LIBS} ${HEADERS} -o ${NAME} -lreadline


clean:
		${RM} ${OBJS}
		@make -C $(LIBFT) clean

fclean:	clean
		${RM} ${NAME}
		@make -C $(LIBFT) fclean

re:		fclean all

.PHONY:	all clean fclean re
