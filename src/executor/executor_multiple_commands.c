/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_multiple_commands.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:54:47 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/25 18:41:29 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_pipes(t_data *data)
{
	int	i;
	t_cmds	*cmd;

	i = 0;
	while (data->pipe_tab[i])
	{
		printf("pipe %i: -%i- -%i-\n", i, data->pipe_tab[i][1], data->pipe_tab[i][0]);
		i++;
	}
	cmd = data->cmd[0];
	while (cmd)
	{
		if (cmd->exec->pipe_in)
			printf("%s in: 1-[%i] 0-[%i]\n", cmd->tab[0], cmd->exec->pipe_in[1], cmd->exec->pipe_in[0]);
		if (cmd->exec->pipe_out)
			printf("%s out: 1-[%i] 0-[%i]\n", cmd->tab[0], cmd->exec->pipe_out[1], cmd->exec->pipe_out[0]);
		cmd = cmd->next;
	}
}

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

void	close_all_fds(t_data *data)
{
	close_all_pipes(data->cmd[0]);
	close_all_files(data->cmd[0]);
}

void	get_last_exit_value(t_data *data)
{
	int	wait_ret;
	int	i;
	t_cmds *cmd;

	wait_ret = 0;
	i = 0;
	cmd = data->cmd[0];
	while (cmd)
	{
		waitpid(data->pid_tab[i], &wait_ret, 0);
		if (i == 0)
			close_all_fds(data);
		cmd = cmd->next;
		g_sig = wait_ret % 255;
		i++;
	}
	return ;
}

void	cmd_pipe_execution(t_cmds *cmd, t_exec *exec)
{
	if (cmd->builtin)
		exit(which_cmd(cmd));
	else
		loop_test(cmd->tab, exec);
}

/*multiple_commands() va créer autant de process*/

void	multiple_commands(t_data *data)
{
	t_cmds	*cmd;
	int		i;

	init_pipes(data);
	prep_cmd_fds(data);
	init_pid_tab(data);
	cmd = data->cmd[0];
	i = 0;
	while (cmd)
	{
		data->pid_tab[i] = fork();
		if (data->pid_tab[i] == 0)
		{
			change_input_output(cmd, cmd->exec);
			close_all_fds(data);
			if (check_input_list(cmd) == NO_ERROR)
				cmd_pipe_execution(cmd, cmd->exec);
			else
				exit(EXIT_FAILURE);
		}
		i++;
		cmd = cmd->next;
	}
	get_last_exit_value(data);
}