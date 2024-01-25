/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command_execution.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:44:04 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/25 14:20:59 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_execution(t_cmds *cmd)
{
	if (!cmd->builtin)
		waitpid(0, &g_sig, 0);
	g_sig = g_sig % 255;
}

int	is_direct_execution(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	loop_test(char **arg, t_exec *exec)
{
	int	i;

	i = 0;
	if (is_direct_execution(arg[0]))
		execve(arg[0], arg, exec->env_tab);
	while (exec->path && exec->path[i])
	{
		exec->test = ft_strjoin_free(exec->path[i], "/", 0);
		exec->test = ft_strjoin_free(exec->test, arg[0], 1);
		if (execve(exec->test, arg, exec->env_tab) == -1)
			i++;
		ft_free_tab(NULL, exec->test);
	}
	putstr_fd_str(arg[0], ": command not found\n", NULL, 2);
	exit(127);
}

void	cmd_execution(t_cmds *cmd, t_exec *exec)
{
	if (cmd->builtin)
		exit(which_cmd(cmd));
	else
		loop_test(cmd->tab, exec);
	check_execution(cmd);
}
