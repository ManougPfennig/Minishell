/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:00:32 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/25 23:38:28 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	multi_free(char *str, char *str2, char *str3)
{
	if (str)
		free(str);
	if (str2)
		free(str2);
	if (str3)
		free(str3);
	return (1);
}

void	free_exec(t_exec *exec)
{
	ft_free_tab(exec->path, exec->test);
	ft_free_tab(exec->env_tab, NULL);
	free(exec);
}

void	free_cmd(t_cmds *cmd)
{
	t_lexer	**redir_ptr;

	redir_ptr = NULL;
	redir_ptr = malloc(sizeof(t_lexer *));
	redir_ptr[0] = cmd->redir;
	free_lexer(redir_ptr);
	ft_free_tab(cmd->tab, cmd->builtin);
}

void	free_after_execution(t_data *data)
{
	t_cmds	*cmd;

	cmd = data->cmd[0];
	free(data->cmd);
	free(data->builtins);
	free_pid_tab(data);
	free_pipe_tab(data);
	while (cmd)
	{
		free_cmd(cmd);
		if (cmd->exec)
			free_exec(cmd->exec);
		if (cmd->prev)
			free(cmd->prev);
		if (!cmd->next)
		{
			free(cmd);
			break ;
		}
		cmd = cmd->next;
	}
}
