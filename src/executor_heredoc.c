/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:17:10 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/04 20:33:37 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(t_lexer *lex, char *end)
{
	char	*buf;

	ft_free_tab(NULL, lex->str);
	lex->str = NULL;
	buf = NULL;
	while (1)
	{
		buf = readline("heredoc> ");
		if (!ft_strcmp(buf, end))
			break ;
		buf = ft_strjoin_free(buf, "\n", 1);
		lex->str = ft_strjoin_free(lex->str, buf, 3);
	}
	ft_free_tab(NULL, buf);
	ft_free_tab(NULL, end);
}

void	find_heredocs(t_data *data)
{
	t_cmds	*cmd;
	t_lexer	*ptr;

	cmd = data->cmd[0];
	while (cmd)
	{
		ptr = cmd->redir;
		while (ptr)
		{
			if (ptr->token == LESS_LESS)
				ft_heredoc(ptr, ft_strdup(ptr->str));
			ptr = ptr->next;
		}
		cmd = cmd->next;
	}
}
