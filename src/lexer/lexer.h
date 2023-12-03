/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:18:40 by mapfenni          #+#    #+#             */
/*   Updated: 2023/11/30 16:21:21 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_data {
	char	*str;
	int		token;
	t_lexer	*next;
	t_lexer	*prev;
}				t_lexer;

typedef struct	s_copy {
	int	len;
	int	start;
	int	i;
	int	y;
}				t_copy;


# define LESS_THAN = 1
# define MORE_THAN = 2
# define PIPE = 3
# define LESS_LESS = 4
# define MORE_MORE = 5

#endif