/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:47:21 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/11 20:58:02 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_lexer(t_lexer **lexed)
{
	t_lexer	*ptr;

	if (!lexed || !(*lexed))
		return ;
	ptr = *lexed;
	while (ptr)
	{
		printf("str: [%s]\ntoken: [%i]\n", ptr->str, ptr->token);
		ptr = ptr->next;
	}
}

void	free_lexer(t_lexer **lexed)
{
	t_lexer	*ptr;
	t_lexer	*ex_ptr;

	if (!lexed)
		return ;
	ptr = *lexed;
	free(lexed);
	while (ptr)
	{
		free(ptr->str);
		ex_ptr = ptr;
		ptr = ptr->next;
		free(ex_ptr);
	}
}
