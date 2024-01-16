/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command_execution.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:44:04 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/16 20:42:20 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_execution(t_cmds *cmd)
{
	if (!cmd->builtin)
		waitpid(0, &g_sig, 0);
	printf("pid ret : %i\n", g_sig % 255);
	g_sig = g_sig % 255;
	if (g_sig == 127)
		printf("%s: command not found\n", cmd->tab[0]);
}

int	loop_test(char **arg, t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->path && exec->path[i])
	{
		exec->test = ft_strjoin_free(exec->path[i], "/", 0);
		exec->test = ft_strjoin_free(exec->test, arg[0], 1);
		execve(arg[0], arg, NULL);
		if (execve(exec->test, arg, NULL) == -1)
			i++;
		ft_free_tab(NULL, exec->test);
	}
	exit(127);
}

void	exec_command(t_cmds *cmd, t_exec *exec, int pipe_fd[2])
{
	pid_t	pid;

	if (cmd->builtin)
	{
		dup2(exec->fd_in, STDIN_FILENO);
		dup2(exec->fd_out, STDOUT_FILENO);
		g_sig = which_cmd(cmd);
		dup2(cmd->data->std_in, STDIN_FILENO);
		dup2(cmd->data->std_out, STDOUT_FILENO);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(exec->fd_in, STDIN_FILENO);
			dup2(exec->fd_out, STDOUT_FILENO);
			close(pipe_fd[0]);
			if (!cmd->tab)
				exit(EXIT_SUCCESS) ;
			else
				loop_test(cmd->tab, exec);
		}
	}
}

void	cmd_execution(t_cmds *cmd, t_exec *exec)
{
	int	pipe_fd[2];

	pipe(pipe_fd);
	change_input_output(cmd, exec, pipe_fd);
	exec->last_pipe = dup(pipe_fd[0]);
	exec_command(cmd, exec, pipe_fd);
	close(pipe_fd[1]);
	check_execution(cmd);
	close(pipe_fd[0]);
	close(exec->stdin_cpy);
	close(exec->stdout_cpy);
	close(exec->fd_in);
	close(exec->fd_out);
}