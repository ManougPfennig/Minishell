# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 15:32:10 by nicolas           #+#    #+#              #
#    Updated: 2023/12/09 11:57:26 by mapfenni         ###   ########.fr        #
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
	   parsing.c \
	   lexer.c \
	   replace_env.c \
	   ft_strjoin_free.c \
	   free_lexer.c \
	   
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