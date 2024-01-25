/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_return_builtin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:21:57 by nicolas           #+#    #+#             */
/*   Updated: 2024/01/20 22:10:34 by mapfenni         ###   ########.fr       */
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
	init_builtins(data);
	while (cmd)
	{
		i = 0;
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

int	which_cmd(t_cmds *cmd)
{
	if (cmd->builtin && ft_strcmp(cmd->builtin, "echo") == 0)
		return (ft_echo(cmd));
	else if (cmd->builtin && ft_strcmp(cmd->builtin, "pwd") == 0)
		return (ft_pwd(cmd));
	else if (cmd->builtin && ft_strcmp(cmd->builtin, "cd") == 0)
		return (ft_cd(cmd));
	else if (cmd->builtin && ft_strcmp(cmd->builtin, "exit") == 0)
		return (ft_exit(cmd));
	else if (cmd->builtin && ft_strcmp(cmd->builtin, "env") == 0)
		return (ft_env(cmd));
	else if (cmd->builtin && ft_strcmp(cmd->builtin, "export") == 0)
		return (ft_export(cmd));
	else if (cmd->builtin && ft_strcmp(cmd->builtin, "unset") == 0)
		return (ft_unset(cmd));
	return (0);
}
