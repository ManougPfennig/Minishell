/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:17:10 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/05 17:00:37 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc(t_data * data, t_lexer *lex, char *end)
{
	char	*buf;

	ft_free_tab(NULL, lex->str);
	lex->str = NULL;
	buf = NULL;
	while (1)
	{
		buf = readline("> ");
		data->line_count++;
		if (!ft_strcmp(buf, end))
			break ;
//		if (CTRL + D)
//			BREAK ;
//		if (CTRL + C)
//			return (1);
		buf = ft_strjoin_free(buf, "\n", 1);
		lex->str = ft_strjoin_free(lex->str, buf, 3);
	}
	ft_free_tab(NULL, buf);
	ft_free_tab(NULL, end);
	return (0);
}

int	find_heredocs(t_data *data)
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
			{
				if(ft_heredoc(data, ptr, ft_strdup(ptr->str)))
					return (1);
			}
			ptr = ptr->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
