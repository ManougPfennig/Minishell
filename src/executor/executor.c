/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 20:10:03 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/07 22:25:49 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	executor(t_data *data)
{
	t_cmds	*cmd;

	cmd = data->cmd[0];
	if (handle_heredocs(data))
		return (1);
	//printf("------------------\n");
	//print_cmd_list(data);
	which_cmd(cmd);
	

	return (0);
}