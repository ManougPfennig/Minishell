/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:47:21 by mapfenni          #+#    #+#             */
/*   Updated: 2023/12/09 11:59:15 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(t_lexer **lexed)
{
	t_lexer	*ptr;
	t_lexer	*ex_ptr;

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
