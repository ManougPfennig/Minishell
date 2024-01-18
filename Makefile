# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 15:32:10 by nicolas           #+#    #+#              #
#    Updated: 2024/01/18 14:53:30 by mapfenni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SOURCES = ./src
OBJECTS = ./bin
AFILE = libft/libft.a

SRCS = main.c \
	   utils/ft_strjoin_free.c \
	   utils/utils.c \
	   utils/utils_2.c \
	   utils/utils_3.c \
	   utils/free_all.c \
	   prompt/prompt.c \
	   builtin/cmd.c \
	   builtin/cd_working.c \
	   builtin/echo_working.c \
	   builtin/exit_working.c \
	   builtin/pwd_working.c \
	   builtin/env_working.c \
	   builtin/init_env.c \
	   builtin/export_working.c \
	   builtin/unset_working.c \
	   lexer/lexer.c \
	   lexer/lexer_replace_env.c \
	   lexer/lexer_replace_env2.c \
	   lexer/lexer_free.c \
	   lexer/lexer_split.c \
	   lexer/lexer_split_quote.c \
	   lexer/lexer_contain_token.c \
	   parser/parser.c \
	   parser/parser_find_redir.c \
	   parser/parser_utils.c \
	   parser/parser_return_builtin.c \
	   parser/parser_store_cmd.c \
	   executor/executor.c \
	   executor/executor_heredoc.c \
	   executor/executor_check_input_list.c \
	   executor/executor_change_input_output.c \
	   executor/executor_get_fd.c \
	   executor/executor_command_execution.c
	   
OBJS = $(addprefix $(OBJECTS)/, $(SRCS:.c=.o))
CFLAGS = -Wall -Wextra -Werror -Iincludes -g
LDFLAGS = -lreadline
CC = gcc
CINCLUDES = -I ./includes

${OBJECTS}/%.o: ${SOURCES}/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CINCLUDES) -o $@ -c $<

all: ${NAME}

${NAME}: ${OBJS}
	$(CC) $(CFLAGS) -o ${NAME} ${OBJS} ${AFILE} $(LDFLAGS)


clean:
	rm -rf ${OBJECTS}

fclean: clean
	rm -f ${NAME}

re: fclean all