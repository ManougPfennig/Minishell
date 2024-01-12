/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_working.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:55:45 by nicolas           #+#    #+#             */
/*   Updated: 2024/01/07 23:10:16 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_cmds *cmd)
{
	cmd->data->buffercwd = getcwd(cmd->data->buffercwd, PATH_MAX);
	write(1, cmd->data->buffercwd, ft_strlen(cmd->data->buffercwd));
	write(1, "\n", 2);
	return ;
}

