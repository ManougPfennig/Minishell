/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:17:10 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/16 19:19:04 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_env_hd(t_data *data, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (is_envchar(str[i + 1]))
			{
				str = to_env(data, ft_strdup(str), i + 1);
				i--;
			}
		}
		i++;
	}
	return (str);
}

int	make_heredoc(t_data *data, t_lexer *lex, char *end)
{
	char	*buffer;

	g_sig = 0;
	ft_free_tab(NULL, lex->str);
	lex->str = NULL;
	buffer = NULL;
	ft_signal();
	while (1)
	{
		g_sig = IN_HD;
		buffer = readline("> ");
		if (g_sig == CTRL_C_HD)
		{
			g_sig = 130;
			return (multi_free(buffer, end, NULL));
		}
		if (buffer == NULL && printf("minishell: warning: here-document \
		wanted \"%s\" at end of file\n", end) && multi_free(end, NULL, NULL))
			return (0);
		if (!ft_strcmp(buffer, end))
			break ;
		buffer = replace_env_hd(data, buffer);
		buffer = ft_strjoin_free(buffer, "\n", 1);
		lex->str = ft_strjoin_free(lex->str, buffer, 3);
	}
	g_sig = 0;
	multi_free(buffer, end, NULL);
	return (0);
}

int	handle_heredocs(t_data *data)
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
				if (make_heredoc(data, ptr, ft_strdup(ptr->str)))
					return (1);
			}
			ptr = ptr->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
