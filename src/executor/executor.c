/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 20:10:03 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/11 20:50:08 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_exec(t_exec *exec)
{
	exec->last_pipe = 0;
	exec->signal = 0;
	exec->fd_in = STDIN_FILENO;
	exec->fd_out = STDOUT_FILENO;
	exec->path = ft_split(getenv("PATH"), ':');
	exec->test = NULL;
}

int	open_empty_fd(void)
{
	int	pipe_fd[2];

	pipe(pipe_fd);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

void	executor(t_data *data)
{
	t_exec	*exec;
	t_cmds	*cmd;

	if (handle_heredocs(data))
		return ;
	exec = malloc(sizeof(t_exec));
	init_exec(exec);
	cmd = data->cmd[0];
	while (cmd)
	{
		cmd->exec = exec;
		if (check_input_list(cmd) == NO_ERROR)
		{
			exec->stdin_cpy = dup(data->std_in);
			exec->stdout_cpy = dup(data->std_out);
			cmd_execution(cmd, exec);
		}
		else
		{
			if (exec->last_pipe)
				close(exec->last_pipe);
			exec->last_pipe = open_empty_fd();
		}
		cmd = cmd->next;
	}
	close(exec->last_pipe);
// free_everything
	if(dup2(data->std_in, STDIN_FILENO))
		perror("dup2 stdin");
}
