# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 15:32:10 by nicolas           #+#    #+#              #
#    Updated: 2023/12/08 12:13:46 by nicolas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SOURCES = ./src
OBJECTS = ./bin

SRCS = main.c \
	   prompt.c \
	   utils.c \
	   utils_2.c \
	   parsing.c \
	   ft_split.c \
	   lexer.c \
	   
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
	$(CC) $(CFLAGS) -o ${NAME} ${OBJS} $(LDFLAGS)


clean:
	rm -rf ${OBJECTS}

fclean: clean
	rm -f ${NAME}

re: fclean all