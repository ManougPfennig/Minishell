/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_multiple_commands.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:54:47 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/25 23:52:25 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_all_fds(t_data *data)
{
	close_all_pipes(data->cmd[0]);
	close_all_files(data->cmd[0]);
}

void	get_last_exit_value(t_data *data)
{
	int		wait_ret;
	int		i;
	t_cmds	*cmd;

	wait_ret = 0;
	i = 0;
	cmd = data->cmd[0];
	while (cmd)
	{
		if (i == 0)
			close_all_fds(data);
		waitpid(data->pid_tab[i], &wait_ret, 0);
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
