/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:06:37 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/05 16:46:04 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
	{
		printf("(null)\n");
		return ;
	}
	while (tab[i])
	{
		printf("-%s- ", tab[i]);
		i++;
	}
	printf("\n");
}

void	print_cmd_list(t_data *data)
{
	t_cmds	*cmd;

	cmd = data->cmd[0];
	while (cmd)
	{
		printf("structure -%p-\n-", cmd);
		printf("redir:\n");
		print_lexer(&(cmd->redir));
		printf("builtin:\n%s\n", cmd->builtin);
		printf("command: ");
		print_tab(cmd->tab);
		cmd = cmd->next;
	}
}

// parser permet de transformer la liste de mots renvoyée par lexer en
// une nouvelle liste de commandes, de trouver et stocker les tokens,
// séparant une commande d'une autre par les pipes.

int	parser(t_data *data)
{
	if (check_error_lexer(data))
		return (0);
	printf("------------------\n");
	init_cmd_list(data); //nombre de structures cmds à malloc et les mettre
	// en liste dans data
	find_redir(data);
	store_cmd(data);
	print_cmd_list(data);
	return_builtin(data);
	return (1);
}
