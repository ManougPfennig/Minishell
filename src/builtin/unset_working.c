/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_working.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:55:57 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/17 09:37:33 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	str_is_in_tab(t_cmds *cmd, char *str)
{
	t_env	*ptr;

	ptr = cmd->data->copy_env;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, str))
			return (1);
		ptr = ptr->next;
	} 																										
	return (0);
}
void	change_var_env(t_cmds *cmd, char *str)
{
	t_env	*ptr;

	ptr = cmd->data->copy_env;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, str))
		{
			ptr->prev = ptr;
			ptr = ptr->next;
			free(ptr);
			return ;
		}
		ptr = ptr->next;
	}
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