/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_find_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 23:44:49 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/03 21:15:24 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// redir_add_back permet d'ajouter un chaînon de liste type t_cmds
// à la fin d'une autre liste.

void	redir_add_back(t_cmds *cmd, t_lexer *new)
{
	t_lexer	*ptr;

	new->next = NULL;
	new->prev = NULL;
	if (!cmd->redir)
		cmd->redir = new;
	else
	{
		ptr = cmd->redir;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
		new->prev = ptr;
	}
}

// lex_remove_word permet de retirer un mot de la liste chaînée lexer,
// en prenant en considéraiton les différentes positions dans la liste.

void	lex_remove_word(t_data *data, t_lexer *ptr, t_lexer *ptr2)
{
	t_lexer	*temp;

	if (!ptr->prev)
	{
		data->lex[0] = ptr2->next;
		if (data->lex[0])
			data->lex[0]->prev = NULL;
	}
	else
	{
		temp = ptr->prev;
		temp->next = ptr2->next;
		if (temp->next)
			temp->next->prev = temp;
	}
	free(ptr->str);
	free(ptr);
}

// find_redir fait défiler la liste chaînée du lexer. Dès qu'il trouve
// un mot contenant un token de redirection (1/2/4/5) il stock le mot d'après
// (en conservant la valeur du token) à la suite dans la liste "redir" de la
// structure t_cmds que pointe cmd. Ces deux mots sont retiré de la liste
// chaîné lexer, le mot token est free. Quand find_redir trouve une pipe,
// il passe à la structure tcmds suivante. Jusqu'à la fin de la liste lexer.

void	find_redir(t_data *data)
{
	t_lexer	*ptr;
	t_cmds	*cmd;
	t_redir	temp;

	ptr = data->lex[0];
	cmd = data->cmd[0];
	while (cmd && ptr)
	{
		if (ptr->token && ptr->token != 3)
		{
			temp.new = ptr->next;
			ptr->next->token = ptr->token;
			temp.tmp = ptr->next->next;
			lex_remove_word(data, ptr, ptr->next);
			redir_add_back(cmd, temp.new);
			ptr = temp.tmp;
		}
		else if (ptr->token == 3)
		{
			cmd = cmd->next;
			ptr = ptr->next;
		}
		else
			ptr = ptr->next;
	}
}
