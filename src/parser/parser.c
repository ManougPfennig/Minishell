/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:06:37 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/18 21:13:01 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// parser permet de transformer la liste de mots renvoyée par lexer en
// une nouvelle liste de commandes, de trouver et stocker les tokens,
// séparant une commande d'une autre par les pipes.

int	parser(t_data *data)
{
	if (check_error_lexer(data))
		return (0);
	init_cmd_list(data);
	find_redir(data);
	store_cmd(data);
	return_builtin(data);
	return (1);
}
