# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 15:32:10 by nicolas           #+#    #+#              #
#    Updated: 2024/01/07 18:36:32 by mapfenni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SOURCES = ./src
OBJECTS = ./bin
AFILE = libft/libft.a

SRCS = main.c \
	   utils/ft_strjoin_free.c \
	   utils/utils.c \
	   prompt/prompt.c \
	   builtin/cmd.c \
	   builtin/cd_working.c \
	   lexer/lexer.c \
	   lexer/lexer_replace_env.c \
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
	   executor/executor_heredoc.c
	   
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