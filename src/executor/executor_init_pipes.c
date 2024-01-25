/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_init_pipes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:18:15 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/25 23:25:01 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmd_lst_len(t_cmds *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

void	init_pipes(t_data *data)
{
	int	**pipe_tab;
	int	len;
	int	i;

	len = cmd_lst_len(data->cmd[0]);
	len--;
	data->pipes = len;
	pipe_tab = malloc((len + 1) * sizeof(int *));
	i = 0;
	while (i < len)
	{
		pipe_tab[i] = malloc(2 * sizeof(int));
		if (pipe(pipe_tab[i]) == -1)
			perror("pipe");
		i++;
	}
	pipe_tab[i] = NULL;
	data->pipe_tab = pipe_tab;
	return ;
}

void	init_pid_tab(t_data *data)
{
	data->pid_tab = malloc((data->pipes + 1) * sizeof(pid_t));
}
