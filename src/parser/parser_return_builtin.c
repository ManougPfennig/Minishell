/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_return_builtin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:21:57 by nicolas           #+#    #+#             */
/*   Updated: 2024/01/08 17:13:01 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	which_cmd(t_cmds *cmd)
{
	if (cmd->builtin && ft_strcmp(cmd->builtin, "echo") == 0)
		ft_echo(cmd);
	else if (cmd->builtin && ft_strcmp(cmd->builtin, "pwd") == 0)
		ft_pwd(cmd);
	else if (cmd->builtin && ft_strcmp(cmd->builtin, "cd") == 0)
		ft_cd(cmd);
	if (cmd->builtin && ft_strcmp(cmd->builtin, "exit") == 0)
		ft_exit(cmd);
	if (cmd->builtin && ft_strcmp(cmd->builtin, "env") == 0)
		ft_env(cmd);
	/*	
	if (ft_strcmp(cmd->builtin, "export") == 0)
		ft_echo(cmd);
	if (ft_strcmp(cmd->builtin, "unset") == 0)
		ft_echo(cmd);*/
}

