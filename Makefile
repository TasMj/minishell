# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tas <tas@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 15:48:33 by tmejri            #+#    #+#              #
#    Updated: 2023/02/27 13:23:19 by tas              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

MAIN			= ./sources/main.c \

BUILTINS		= ./sources/builtins/ft_cd.c ./sources/builtins/ft_echo.c \
				./sources/builtins/ft_env.c ./sources/builtins/ft_exit.c \
				./sources/builtins/ft_export.c ./sources/builtins/ft_pwd.c \
				./sources/builtins/ft_unset.c \
				
EXIT			= ./sources/exit/error.c ./sources/exit/free.c \

INITIALISATION	= ./sources/initialisation/init_struct.c \

LEXER			= ./sources/lexer/tocken.c ./sources/lexer/lexical_analisis.c \
				./sources/lexer/semantic_analisis.c ./source/lexer/syntactic_analisis.c \

PARSING			= ./sources/parsing/check_args.c ./sources/parsing/input.c \
				./sources/parsing/quoting.c \

TOOLS			= ./sources/tools/tools.c \

SRCS			= ${MAIN} ${BUILTINS} ${EXIT} ${INITIALISATION} ${PARSING} ${TOOLS}

OBJS			= ${SRCS:.c=.o}

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g -I includes/


all:			${NAME}

${NAME}:		${OBJS}
						${CC} ${CFLAGS} ${OBJS} -L/usr/includes -lreadline -o ${NAME}

clean:
						${RM} ${OBJS}

fclean:			clean
						${RM} ${NAME}

re:				fclean ${NAME}

.PHONY:			all clean fclean re