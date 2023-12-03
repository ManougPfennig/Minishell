# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/28 12:52:11 by mapfenni          #+#    #+#              #
#    Updated: 2023/11/23 14:07:39 by mapfenni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = src/test.c

AFILE = incl/libft/libft.a

OBJS = ${SRCS:.c=.o}


CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJS}
	@gcc ${CFLAGS} ${OBJS} ${AFILE} -o ${NAME}

clean:
	rm -f ${OBJS} ${BONUS}

fclean: clean
	rm -f ${NAME}

re: fclean all