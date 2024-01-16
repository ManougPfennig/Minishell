/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_working.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:03:07 by npatron           #+#    #+#             */
/*   Updated: 2024/01/16 21:47:23 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_env(t_cmds *cmd)
{
	t_env	*ptr;

	ptr = cmd->data->copy_env;
	while (ptr)
	{
		if (ptr->equal)
		{
			write(1, ptr->name, ft_strlen(ptr->name));
			write(1, "=", 1);
			write(1, ptr->value, ft_strlen(ptr->value));
			write(1, "\n", 1);
		}
		ptr = ptr->next;
	}
}