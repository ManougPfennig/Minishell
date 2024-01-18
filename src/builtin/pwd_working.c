/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_working.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:55:45 by nicolas           #+#    #+#             */
/*   Updated: 2024/01/18 19:39:02 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_cmds *cmd)
{
	cmd->data->buffercwd = getcwd(cmd->data->buffercwd, PATH_MAX);
	write(1, cmd->data->buffercwd, ft_strlen(cmd->data->buffercwd));
	write(1, "\n", 2);
	return (0);
}
