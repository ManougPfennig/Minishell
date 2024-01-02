/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:06:37 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/02 11:57:19 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_list(t_data *data)
{
	t_cmds	*ptr;

	ptr = data->cmd[0];
	while (ptr)
	{
		printf("-%p-\n-", ptr);
		print_lexer(&(ptr->redir));
		ptr = ptr->next;
	}
}

// parser permet de transformer la liste de mots renvoyée par lexer en
// une nouvelle liste de commandes, séparant une commande d'une autre
// par les pipes.

int	parser(t_data *data)
{
	if (check_error_lexer(data))
		return (0);
	init_cmd_list(data); //nombre de structures cmds à malloc et les mettre en liste dans data
	find_redir(data); //trouver et stocker les tokens
	print_cmd_list(data);
	printf("------------------\n");
	print_lexer(data->lex);
	// store_cmd(data);
	// is_builtin(data);
	return (0);
}
