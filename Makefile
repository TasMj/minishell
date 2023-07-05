# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 15:48:33 by tmejri            #+#    #+#              #
#    Updated: 2023/07/05 18:01:43 by jthuysba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

MAIN			= ./sources/main.c

BUILTINS		= ./sources/builtins/ft_cd.c ./sources/builtins/ft_echo.c \
				./sources/builtins/ft_env.c ./sources/builtins/ft_exit.c \
				./sources/builtins/ft_export.c ./sources/builtins/ft_pwd.c \
				./sources/builtins/ft_unset.c \
		
EXEC			= ./sources/exec/builtin.c ./sources/exec/child_process.c \
				./sources/exec/destroy_all.c ./sources/exec/exec_heredoc.c \
				./sources/exec/exec.c ./sources/exec/handle_redir.c \
				./sources/exec/open_pipes.c ./sources/exec/path.c \
				./sources/exec/prep_cmd.c ./sources/exec/signal.c \
				./sources/exec/heredoc_tools.c ./sources/exec/exec_tools.c \
				./sources/exec/prep_cmd_tools.c ./sources/exec/signal_handlers.c \

EXIT			= ./sources/exit/error.c ./sources/exit/free.c \

PARSING			= ./sources/parsing/check_type.c ./sources/parsing/create_token.c \
				./sources/parsing/preparsing.c ./sources/parsing/quotes.c \
				./sources/parsing/substitution.c \
				./sources/parsing/substitution2.c ./sources/parsing/type.c  \
				

TOOLS			= ./sources/tools/ft_split.c ./sources/tools/tools_builtin.c \
				./sources/tools/tools_builtin2.c  ./sources/tools/tools_exec.c \
				./sources/tools/tools_list.c ./sources/tools/tools_parsing.c \
				./sources/tools/tools.c ./sources/tools/tools2.c \
				./sources/tools/utils.c \

SRCS			= ${MAIN} ${BUILTINS} ${EXEC} ${EXIT} ${PARSING} ${TOOLS}

OBJS			= ${SRCS:.c=.o}

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g -I includes/ 
SUPP			= printf "{\n    leak readline\n    Memcheck:Leak\n    ...\n    fun:readline\n}\n{\n    leak add_history\n   Memcheck:Leak\n    ...\n    fun:add_history\n}" > ignore_leak.supp


all:			${NAME}

${OBJS}: %.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

${NAME}:		${OBJS}
						${CC} ${CFLAGS} ${OBJS} -L/usr/includes -lreadline -o ${NAME}
						${SUPP}

clean:
						${RM} ${OBJS}

fclean:			clean
						${RM} ${NAME}
						${RM} ignore_leak.supp

re:				fclean ${NAME}

ms	: all
		valgrind --suppressions=ignore_leak.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes -s ./minishell

.PHONY:			all clean fclean re
