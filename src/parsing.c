/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:06:37 by mapfenni          #+#    #+#             */
/*   Updated: 2023/12/23 17:03:50 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_data *data)
{
	t_lexer	*ptr;

	ptr = data->lex[0];
	while (ptr)
	{
		ptr->str = replace_env(ptr->str);
		ptr = ptr->next;
	}
}
