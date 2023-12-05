/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:36:38 by mapfenni          #+#    #+#             */
/*   Updated: 2023/12/04 19:24:28 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/minishell.h"
#include "src/lexer.h"

int	main(int ac, char **av)
{
	struct s_lexer	**lexed;
	struct s_lexer	*link;

	(void)ac;
	lexed = lexer(av[1]);
	(void)lexed;
	link = *lexed;
	while (link)
	{
		printf("own: %p\nprev: %p\nstr: %s\ntoken : %i\nnext : %p\n\n", link, link->prev, link->str, link->token, link->next);
		link = link->next;
	}
	return (0);
}