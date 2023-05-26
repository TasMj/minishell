# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 15:48:33 by tmejri            #+#    #+#              #
#    Updated: 2023/05/26 12:55:02 by jthuysba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

MAIN			= ./sources/main.c

BUILTINS		= ./sources/builtins/ft_cd.c ./sources/builtins/ft_echo.c \
				./sources/builtins/ft_env.c \
				./sources/builtins/ft_export.c ./sources/builtins/ft_pwd.c \
				./sources/builtins/ft_unset.c \
		
EXEC			= ./sources/exec/path.c \
				./sources/exec/heredoc.c \
				./sources/exec/builtin.c \
				./sources/exec/signal.c \
				./sources/exec/clean_all.c ./sources/exec/setup_pipes.c \
				./sources/exec/exec_utils.c ./sources/exec/exec.c \
				./sources/exec/set_fd.c ./sources/exec/exec_all.c \

EXIT			= ./sources/exit/error.c ./sources/exit/free.c \
				./sources/exit/free_struct.c

PARSING			= ./sources/parsing/create_token.c ./sources/parsing/quotes.c \
				./sources/parsing/check_type.c ./sources/parsing/substitution.c \
				./sources/parsing/type.c ./sources/parsing/preparsing.c \
				./sources/parsing/substitution2.c \

TOOLS			= ./sources/tools/ft_split.c ./sources/tools/tools_exec.c \
				./sources/tools/tools_list.c ./sources/tools/tools_parsing.c \
				./sources/tools/tools.c ./sources/tools/tools_builtin.c \
				./sources/tools/tools_builtin2.c ./sources/tools/tools2.c \
				./sources/tools/tools_redir.c 

SRCS			= ${MAIN} ${BUILTINS} ${EXEC} ${EXIT} ${PARSING} ${TOOLS}

OBJS			= ${SRCS:.c=.o}

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g -I includes/ 


all:			${NAME}

${OBJS}: %.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

${NAME}:		${OBJS}
						${CC} ${CFLAGS} ${OBJS} -L/usr/includes -lreadline -o ${NAME}

clean:
						${RM} ${OBJS}

fclean:			clean
						${RM} ${NAME}

re:				fclean ${NAME}

.PHONY:			all clean fclean re