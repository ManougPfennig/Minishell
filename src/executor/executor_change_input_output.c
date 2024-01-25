/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_change_input_output.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:46:04 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/25 13:43:30 by mapfenni         ###   ########.fr       */
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

void	change_input_output(t_cmds *cmd, t_exec *exec)
{
	int	*pipe_in;
	int	*pipe_out;

	pipe_in = exec->pipe_in;
	pipe_out = exec->pipe_out;
	if (exec->fd_in == NO_FILE)
	{
		if (cmd->prev)
			do_dup2(pipe_in[0], STDIN_FILENO);
	}
	else
		do_dup2(exec->fd_in, STDIN_FILENO);
	if (exec->fd_out == NO_FILE)
	{
		if (cmd->next)
			do_dup2(pipe_out[1], STDOUT_FILENO);
	}
	else
		do_dup2(exec->fd_out, STDOUT_FILENO);
}
