# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 15:48:33 by tmejri            #+#    #+#              #
#    Updated: 2023/02/20 18:17:15 by tmejri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

SRCS			= parsing.c \

OBJS			= ${SRCS:.c=.o}

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g3 -lreadline


all:			${NAME}

${NAME}:		${OBJS}
						${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
						${RM} ${OBJS}

fclean:			clean
						${RM} ${NAME}

re:				fclean ${NAME}

.PHONY:			all clean fclean re