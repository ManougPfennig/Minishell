/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_return_builtin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:21:57 by nicolas           #+#    #+#             */
/*   Updated: 2024/01/05 16:55:42 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_builtins(t_data *data)
{
	data->builtins = malloc(sizeof(char *) * 8);
	data->builtins[0] = "echo";
	data->builtins[1] = "cd";
	data->builtins[2] = "export";
	data->builtins[3] = "unset";
	data->builtins[4] = "pwd";
	data->builtins[5] = "env";
	data->builtins[6] = "exit";
	data->builtins[7] = NULL;
}

void	return_builtin(t_data *data)
{
	t_cmds	*cmd;
	int		i;
	int		j;

	cmd = data->cmd[0];
	i = 0;
	init_builtins(data);
	while (cmd)
	{
		j = 0;
		while (cmd->tab && data->builtins[i] && j == 0)
		{
			if (ft_strcmp(data->builtins[i], cmd->tab[0]) == 0)
			{
				cmd->builtin = ft_strdup(data->builtins[i]);
				j += 1;
			}
			else
				cmd->builtin = NULL;
			i++;
		}
		cmd = cmd->next;
	}
}
