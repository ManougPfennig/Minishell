/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:06:37 by mapfenni          #+#    #+#             */
/*   Updated: 2023/12/30 11:37:29 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_list(t_data *data)
{
	t_cmds	*ptr;

	ptr = data->cmd[0];
	while (ptr)
	{
		printf("-%p-\n", ptr);
		ptr = ptr->next;
	}
}

int	parser(t_data *data)
{
	if (check_error_lexer(data))
		return (1);
	init_cmd_list(data); //nombre de structures cmds à malloc et les mettre en liste dans data
	//find_redir(data); //trouver et stocker les tokens
//	print_cmd_list(data);
	// store_cmd(data);
	// is_builtin(data);
	return (0);
}
