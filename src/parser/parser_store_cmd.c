/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_store_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:02:43 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/07 18:38:47 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// add_command fait l'allocation et le remplissage du tableau

void	add_command(t_lexer *ptr, int len, t_cmds *cmd)
{
	int		i;
	char	**new;

	i = 0;
	if (len == 0)
		return ;
	new = (char **)malloc((len + 1) * sizeof(char *));
	new[len] = NULL;
	while (ptr && ptr->token != PIPE && i < len)
	{
		new[i] = ft_strdup(ptr->str);
		ptr = ptr->next;
		i++;
	}
	cmd->tab = new;
}

// store_cmd compte le nombre de chaînons jusqu'au prochain
// pipe ou la fin de la liste. Un tableau de cette taille est
// malloc puis rempli avec des copies des strings de la chaîne
// afin de garder uniquement la commande et ses arguments.

void	store_cmd(t_data *data)
{
	t_cmds	*cmd;
	t_lexer	*ptr;
	t_lexer	*temp;
	int		len;

	cmd = data->cmd[0];
	ptr = data->lex[0];
	while (cmd)
	{
		len = 0;
		temp = ptr;
		while (ptr && ptr->token != PIPE)
		{
			len++;
			ptr = ptr->next;
		}
		add_command(temp, len, cmd);
		if (ptr)
			ptr = ptr->next;
		cmd = cmd->next;
	}
}

/*
⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣶⣶⠿⠟⠛⠲⣶⣴⣦⣤⣤⡀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⣠⣶⣿⡿⠿⠧⣀⣕⢤⣶⣾⣮⣿⡛⢿⣿⠏⣆⠀⠀⠀⠀⠀⠀
⠀⠀⠀⢀⣴⣟⣿⣿⠿⣷⠛⠛⡛⠻⡋⠉⢉⠙⠉⡱⣅⡨⢠⣌⢲⣤⡀⠀⠀⠀
⠀⠀⣴⡿⣽⣿⣍⠛⠒⢄⣾⣾⣿⣼⣾⣾⣿⣿⣷⣿⣿⣿⣿⡿⢊⠤⣷⡄⠀⠀
⠀⢠⣿⣟⣛⡿⣿⣭⠻⠿⠻⠿⠻⠛⠿⠽⠿⠿⠟⠟⠟⠛⠉⠰⣿⣿⡞⣿⠀⠀
⠀⢸⣿⣿⣿⡿⠃⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠿⣯⣘⣇⠀
⠀⢸⣿⣿⣻⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⡆⢽⠀
⠀⢸⣿⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⡇⠀
⠀⠈⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⠃⠀
⠀⢀⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢼⣿⡀⠀
⠸⢁⠈⣿⠀⠀⠀⠀⠀⠀⠀⢰⣶⡄⠀⠀⢶⣲⠀⠀⠀⠀⠀⠀⠀⠀⢸⠃⡌⢂
⡇⣿⢆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠁⠀⠀⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠈⠸⢸⢸
⠇⠃⡎⢰⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡶⠶⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⢊⣧⢀⠆
⠰⠈⡳⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠀⠀⠸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠅⡎⠀
⠀⠱⡉⠁⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡶⠴⠁⠀
⠀⠀⠑⠒⡇⠀⠀⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡞⠀⢰⠁⠀⠀⠀
⠀⠀⠀⠀⢸⡀⠀⠱⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⠀⢀⡏⠀⠀⠀⠀
⠀⠀⠀⠀⠀⢣⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠇⠀⡜⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠑⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢀⠞⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠈⠳⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠔⠁⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠑⢄⣀⠀⠀⠀⠀⢀⣀⠔⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀
Faire des tests pendant 2h pour savoir pourquoi
Valgrind m'envoie 3000 erreurs...
j'ai écris :
malloc((len + 1) + sizeof(char *));
au lieu de :
malloc((len + 1) * sizeof(char *));
*/