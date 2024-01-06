/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:17:10 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/06 16:07:24 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc(t_lexer *lex, char *end)
{
	char	*buf;

	g_sig = 0;
	ft_free_tab(NULL, lex->str);
	lex->str = NULL;
	buf = NULL;
	ft_signal();
	while (1)
	{
		g_sig = IN_HD;
		buf = readline("> ");
		if (g_sig == 2)
			return (1);
		if (buf == NULL)
		{
			printf("minishell: warning: here-document wanted \"%s\" at end of file\n", end);
			return (1);
		}
		if (!ft_strcmp(buf, end))
			break ;
		buf = ft_strjoin_free(buf, "\n", 1);
		lex->str = ft_strjoin_free(lex->str, buf, 3);
	}
	g_sig = 0;
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
				if (ft_heredoc(ptr, ft_strdup(ptr->str)))
					return (1);
			}
			ptr = ptr->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
