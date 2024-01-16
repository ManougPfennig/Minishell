/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_working.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:54:15 by npatron           #+#    #+#             */
/*   Updated: 2024/01/16 18:08:37 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int there_is_variable_export(t_cmds *cmd, char *str)
{
    char    *compare;
    int     i;

    i = 0;
    compare = ft_addstring("declare -x ", str);
    if (there_is_egual(str) == 0)
        return (0);
    while (cmd->data->env_export[i])
    {
        if (ft_strncmp(compare, cmd->data->env_export[i], ft_strlen(compare)) == 0)
            return (1); 
        i++;
    }
    return (0);
}

int there_is_variable_env(t_cmds *cmd, char *str)
{
    int     i;

    i = 0;
    if (there_is_egual(str) == 0)
        return (0);
    while (cmd->data->copy_env[i])
    {
        if (ft_strncmp(str, cmd->data->copy_env[i], ft_strlen(str)) == 0)
            return (1); 
        i++;
    }
    return (0);
}

void    erase_variable_export(t_cmds *cmd, char *str)
{
	char	**tab;
	char	*compare;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * (len_tab(cmd->data->env_export)));
	compare = ft_addstring("declare -x ", str);
	while (cmd->data->env_export[i])
    {
		if (ft_strncmp(compare, cmd->data->env_export[i], ft_strlen(compare)) == 0)
        {
            i++;
            continue;
        }
		tab[j] = cmd->data->env_export[i]; 
        i++;
		j++;
    }
	tab[j] = NULL;
	cmd->data->env_export = copy_tab(tab);    
}

void    erase_variable_env(t_cmds *cmd, char *str)
{
	char	**tab;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * (len_tab(cmd->data->copy_env)));
	while (cmd->data->copy_env[i])
    {
		if (ft_strncmp(str, cmd->data->copy_env[i], ft_strlen(str)) == 0)
        {
            i++;
            continue;
        }
		tab[j] = cmd->data->copy_env[i];
        i++;
		j++;
    }
	tab[j] = NULL;
	cmd->data->copy_env = copy_tab(tab);    
}

void    ft_unset(t_cmds *cmd)
{
    int i;

    i = 1;
    while (cmd->tab[i])
    {
        if (there_is_variable_export(cmd, cmd->tab[i]) == 1)
			erase_variable_export(cmd, cmd->tab[i]);
        if (there_is_variable_env(cmd, cmd->tab[i]) == 1)
            erase_variable_env(cmd, cmd->tab[i]);
        i++;
    }
}