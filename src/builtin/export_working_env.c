/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_working_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:56:25 by npatron           #+#    #+#             */
/*   Updated: 2024/01/15 11:32:41 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int change_env(t_cmds *cmd, char *str)
{
    int i;
    int j;
    i = 0;
    j = 0;
    
    while (str[j] && str[j] != '=')
        j++;
    while (cmd->data->copy_env[i])
    {
        if (ft_strncmp(str, cmd->data->copy_env[i], j) == 0)
        {
           	cmd->data->copy_env[i] = ft_strdup(str);
            return (1);
        }
        i++;
    }
	return (0);
}

void    add_env(t_cmds *cmd, char *str)
{
	char	**tab;
	int		i;

	i = 0;
	if (there_is_egual(str) == 1 || change_env(cmd, str) == 1 || check_var(str) == 1)
    {
		return ;
    }
	tab = malloc(sizeof(char *) * (len_tab(cmd->data->copy_env) + 2));
	while (cmd->data->copy_env[i])
	{
		tab[i] = ft_strdup(cmd->data->copy_env[i]);
		i++;
	}
	tab[i] = ft_strdup(str);
	i++;
	tab[i] = NULL;
	cmd->data->copy_env = copy_tab(tab);
}

void    ft_export(t_cmds *cmd)
{
	int	i;

	i = 1;
	while (cmd->tab[i])
	{
		add_env(cmd, cmd->tab[i]);
		add_export(cmd, cmd->tab[i]);
		i++;
	}
}
