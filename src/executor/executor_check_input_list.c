/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_check_input_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:34:12 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/11 19:48:27 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_file(char *str)
{
	int	fd;

	fd = open(str, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	close(fd);
}

int	check_acces_file(t_lexer *lex)
{
	if ((lex->token == 2 || lex->token == 5) && access(lex->str, F_OK))
		create_file(lex->str);
	if (lex->token == 1 && access(lex->str, F_OK))
	{
		printf("minishell: %s: No such file or directory\n", lex->str);
		return (ERROR);
	}
	else if (lex->token == 1 && access(lex->str, R_OK))
	{
		printf("minishell: %s: Permission denied\n", lex->str);
		return (ERROR);
	}
	else if ((lex->token == 2 || lex->token == 5) && access(lex->str, W_OK))
	{
		printf("minishell: %s: Permission denied\n", lex->str);
		return (ERROR);
	}
	else if (lex->token == 2)
		close(open(lex->str, O_WRONLY | O_TRUNC));
	return (NO_ERROR);
}

int	check_input_list(t_cmds *cmd)
{
	t_lexer	*lex;

	lex = cmd->redir;
	while (lex)
	{
		if (lex->token == 1 || lex->token == 2 || lex->token == 5)
		{
			if (check_acces_file(lex) == ERROR)
				return (ERROR);
		}
		lex = lex->next;
	}
	return (NO_ERROR);
}