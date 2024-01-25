/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_init_cmds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 23:28:46 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/25 23:30:07 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prep_cmd_fds(t_data *data)
{
	t_cmds	*cmd;
	int		i;

	cmd = data->cmd[0];
	while (cmd)
	{
		cmd->exec = init_exec(data);
		cmd = cmd->next;
	}
	cmd = data->cmd[0];
	i = 0;
	while (cmd)
	{
		cmd->exec->fd_in = input_fd(cmd);
		cmd->exec->fd_out = output_fd(cmd);
		cmd->exec->pipe_out = cmd->data->pipe_tab[i];
		if (cmd->next)
			cmd->next->exec->pipe_in = cmd->data->pipe_tab[i];
		i++;
		cmd = cmd->next;
	}
}

void	close_all_pipes(t_cmds *cmd)
{
	t_exec	*exec;

	while (cmd)
	{
		exec = cmd->exec;
		if (exec->pipe_out)
		{
			do_close(exec->pipe_out[1]);
			do_close(exec->pipe_out[0]);
		}
		cmd = cmd->next;
	}
}

void	close_all_files(t_cmds *cmd)
{
	t_exec	*exec;

	while (cmd)
	{
		exec = cmd->exec;
		if (exec->fd_in != NO_FILE)
			do_close(exec->fd_in);
		if (exec->fd_out != NO_FILE)
			do_close(exec->fd_out);
		cmd = cmd->next;
	}
}
