# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 15:32:10 by nicolas           #+#    #+#              #
#    Updated: 2024/01/03 18:05:56 by mapfenni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SOURCES = ./src
OBJECTS = ./bin
AFILE = libft/libft.a

SRCS = main.c \
	   prompt.c \
	   utils.c \
	   cmd.c \
	   cd_working.c \
	   ft_strjoin_free.c \
	   lexer.c \
	   lexer_replace_env.c \
	   lexer_free.c \
	   lexer_split.c \
	   lexer_split_quote.c \
	   lexer_contain_token.c \
	   parser.c \
	   parser_find_redir.c \
	   parser_utils.c \
	   parser_store_cmd.c
	   
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