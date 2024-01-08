/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_working.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:03:07 by npatron           #+#    #+#             */
/*   Updated: 2024/01/08 17:12:40 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_env(t_cmds *cmd)
{
    int	i;

	i = 0;
	while (cmd->data->copy_env[i])
	{
		write(1, cmd->data->copy_env[i], ft_strlen(cmd->data->copy_env[i]));
        write(1, "\n", 1);
		i++;
	}
}