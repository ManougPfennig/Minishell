/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_change_input_output.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:46:04 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/15 23:11:23 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*lexer_last_input(t_lexer *lex)
{
	t_lexer	*in;

	in = NULL;
	while (lex)
	{
		if (lex->token == 1 || lex->token == 4)
			in = lex;
		lex = lex->next;
	}
	return (in);
}

t_lexer	*lexer_last_output(t_lexer *lex)
{
	t_lexer	*out;

	out = NULL;
	while (lex)
	{
		if (lex->token == 2 || lex->token == 5)
			out = lex;
		lex = lex->next;
	}
	return (out);
}

void	change_input_output(t_cmds *cmd, t_exec *exec, int pipe_fd[2])
{
	t_lexer	*input;
	t_lexer	*output;

	input = lexer_last_input(cmd->redir);
	output = lexer_last_output(cmd->redir);
	if (input)
		exec->fd_in = get_input_fd(input, cmd);
	else if (cmd->prev)
		exec->fd_in = exec->last_pipe;
	else
		exec->fd_in = exec->stdin_cpy;
	if (output)
		exec->fd_out = get_output_fd(output);
	else if (cmd->next)
		exec->fd_out = pipe_fd[1];
	else
		exec->fd_out = exec->stdout_cpy;
}
