/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_working.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:55:57 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/18 17:21:18 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(t_env *ptr)
{
	free(ptr->name);
	free(ptr->value);
	free(ptr);
}

t_env	*str_is_in_tab(t_cmds *cmd, char *str)
{
	t_env	*ptr;

	ptr = cmd->data->copy_env;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, str) == 0)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

void	change_var_env(t_cmds *cmd, char *str)
{
	t_env	*ptr;

	ptr = str_is_in_tab(cmd, str);
	if (ptr->prev)
	{
		ptr->prev->next = ptr->next;
		if (ptr->next)
			ptr->next->prev = ptr->prev;
	}
	else
		cmd->data->copy_env = ptr->next;
	free_env(ptr);
}

int	ft_unset(t_cmds *cmd)
{
	int		i;

	i = 1;
	while (cmd->tab[i])
	{
		if (str_is_in_tab(cmd, cmd->tab[i]))
			change_var_env(cmd, cmd->tab[i]);
		i++;
	}
	return (0);
}
