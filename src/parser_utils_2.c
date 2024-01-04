/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:21:57 by nicolas           #+#    #+#             */
/*   Updated: 2024/01/04 13:38:44 by nicolas          ###   ########.fr       */
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
	int		count;

	cmd = data->cmd[0];
	count = data->pipes + 1;
	while (count != 0)
	{
		j = 0;
		while (data->builtins[i] || j != 0)
		{
			if (ft_strcmp(data->builtins[i], cmd->tab[0]) == 1)
			{
				cmd->builtin = ft_strdup(data->builtins[i]);
				j += 1;
			}
			else
				cmd->builtin = ft_strdup("NULL");
			i++;
		}
		cmd = cmd->next;
		count--;
	}
}
