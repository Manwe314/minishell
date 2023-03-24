# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 19:53:49 by lkukhale          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2023/03/20 14:28:04 by beaudibe         ###   ########.fr        #
=======
#    Updated: 2023/03/21 19:36:23 by lkukhale         ###   ########.fr        #
>>>>>>> origin/lkukhale
#                                                                              #
# **************************************************************************** #

NAME 		= minishell
USER		= lkukhale
SRCS 		= ${shell find ./src -iname "*.c"}

HEADERS		= -I ./includes/
LIBS		= ${LIBFT}/libft.a
LIBFT		= ./lib/libft
CFLAGS		= -Wall -Wextra -Werror
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
