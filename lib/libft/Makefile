# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 19:53:49 by lkukhale          #+#    #+#              #
#    Updated: 2023/06/30 16:52:37 by lkukhale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= libft.a
SRCS 		= $(addsuffix .c, \
			ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha ft_isdigit ft_isascii \
			ft_isprint ft_itoa ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset \
			ft_putchar_fd ft_putendl_fd ft_putstr_fd ft_putnbr_fd ft_split ft_strchr \
			ft_strdup ft_striteri ft_strjoin ft_strlcat ft_strlcpy ft_strlen \
			ft_strmapi ft_strncmp ft_strnstr ft_strrchr ft_strtrim ft_substr \
			ft_tolower ft_toupper)
BNSRCS		= $(addsuffix .c, \
			ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back \
			ft_lstdelone ft_lstclear ft_lstiter ft_lstmap)
AR			= ar
ARFLAGS		= rc
RANLIB		= ranlib
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM 			= rm -f

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

OBJS	= ${SRCS:.c=.o}
BNOBJS	= ${BNSRCS:.c=.o}

${NAME}:	${OBJS}
		${AR} ${ARFLAGS} ${NAME} ${OBJS}
		${RANLIB} ${NAME}

all:	${NAME}

bonus:	${BNOBJS} ${OBJS}
		${AR} ${ARFLAGS} ${NAME} ${OBJS} ${BNOBJS}
		${RANLIB} ${NAME}

clean:
		${RM} ${OBJS}
		${RM} ${BNOBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re
