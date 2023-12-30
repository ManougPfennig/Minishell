/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 23:44:49 by mapfenni          #+#    #+#             */
/*   Updated: 2023/12/30 13:02:38 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_add_back(t_cmds *cmd, t_lexer *new)
{
	t_lexer	*ptr;

	new->token = new->prev->token;
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

void	find_redir(t_data *data)
{
	t_lexer	*ptr;
	t_cmds	*cmd;
	t_redir	temp;

	ptr = data->lex[0];
	cmd = data->cmd[0];
	while (cmd && ptr)
	{
		if (ptr && ptr->token && ptr->token != 3)
		{
			temp.new = ptr->next;
			ptr->prev->next = ptr->next->next;
			if (ptr->next->next)
				ptr->next->next = ptr->prev;
			ptr = ptr->next->next;
			redir_add_back(cmd, temp.new);
		}
		if (ptr && ptr->token == 3)
			cmd = cmd->next;
		if (ptr)
			ptr = ptr->next;
	}
}