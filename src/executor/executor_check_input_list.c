/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_check_input_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:34:12 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/25 23:59:20 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*create_file() créé un fichier avec un nom donné, avec les droit standards
Read-Write-Execute donné aux nouveaux fichiers dans bash.*/

void	create_file(char *str)
{
	int	fd;

	fd = open(str, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	close(fd);
}

/*check_access_file() teste de différentes manières les accès des fichiers
de redirections pour afficher un message d'erreur si il y en a une ou alors
créer les fichiers manquants.*/

int	check_acces_file(t_lexer *lex)
{
	if (!lex->str && putstr_fd("minishell: ambiguous redirect\n", 2))
		return (ERROR);
	if ((lex->token == MORE_THAN || lex->token == MORE_MORE)
		&& access(lex->str, F_OK))
		create_file(lex->str);
	if (lex->token == LESS_THAN && access(lex->str, F_OK))
	{
		putstr_fd_str("minishell: ", lex->str, ": No such file or \
directory\n", 2);
		return (ERROR);
	}
	else if (lex->token == LESS_THAN && access(lex->str, R_OK))
	{
		putstr_fd_str("minishell: ", lex->str, ": Permission denied\n", 2);
		return (ERROR);
	}
	else if ((lex->token == MORE_THAN || lex->token == MORE_MORE)
		&& access(lex->str, W_OK))
	{
		putstr_fd_str("minishell: ", lex->str, ": Permission denied\n", 2);
		return (ERROR);
	}
	else if (lex->token == MORE_THAN)
		close(open(lex->str, O_WRONLY | O_TRUNC));
	return (NO_ERROR);
}

/*check_input_list() va faire défiler la liste d'inputs dans une commande
donnée afin de vérifier les cas d'erreurs de redirections possibles.
Dans le cas d'une erreur, elle return ERROR, ce qui empêchera la commande
concernée de s'exécuter et le process se terminera avec un signal d'erreur.
Un message d'erreur sera écrit sur le fd STDERR (2).*/

int	check_input_list(t_cmds *cmd)
{
	t_lexer	*lex;

	lex = cmd->redir;
	while (lex)
	{
		if (lex->token == 1 || lex->token == 2 || lex->token == 5)
		{
			if (check_acces_file(lex) == ERROR)
			{
				g_sig = 1;
				return (ERROR);
			}
		}
		lex = lex->next;
	}
	return (NO_ERROR);
}
