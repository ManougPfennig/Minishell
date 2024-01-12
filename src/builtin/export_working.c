/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_working.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:56:25 by npatron           #+#    #+#             */
/*   Updated: 2024/01/12 13:16:36 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	same_variable(t_cmds *cmd, char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[j] != '=')
        j++;
    while (cmd->data->new_copy_env[i])
    {
        if (ft_strncmp(str, cmd->data->new_copy_env[i], j) == 0)
            return (1) ;
        i++;
    }
	return (0);
}

int change_env(t_cmds *cmd, char *str)
{
    int i;
    int j;
    i = 0;
    j = 0;
    
    while (str[j] != '=')
        j++;
    while (cmd->data->new_copy_env[i])
    {
        if (ft_strncmp(str, cmd->data->new_copy_env[i], j) == 0)
        {
            cmd->data->new_copy_env[i] = ft_strdup(str);
            free(cmd->data->copy_env);
            cmd->data->copy_env = copy_tab(cmd->data->new_copy_env);
            return (1);
        }
        i++;
    }
    free(cmd->data->copy_env);
    cmd->data->copy_env = copy_tab(cmd->data->new_copy_env);
	return (0);
}

void    init_new_env(t_cmds *cmd, int j)
{
    char    *str;
    int     i;

    i = 0;
    str = find_variable(cmd, j);
    if (change_env(cmd, str) == 1 || check_var(str) == 1)
        return ;
    free(cmd->data->new_copy_env);
    cmd->data->new_copy_env = malloc(sizeof(char *) * (len_tab(cmd->data->copy_env) + 2));
    while (cmd->data->copy_env[i])
    {
        cmd->data->new_copy_env[i] = ft_strdup(cmd->data->copy_env[i]);
        i++;
    }
    cmd->data->new_copy_env[i] = ft_strdup(str);
    i++;
    cmd->data->new_copy_env[i] = NULL;
    free(cmd->data->copy_env);
    cmd->data->copy_env = copy_tab(cmd->data->new_copy_env);
}

void    init_export_tab(t_data *data)
{
    int	i;

	i = 0;
	data->env_export = malloc(sizeof(char *) * (len_tab(data->copy_env) + 1));
	while (data->copy_env[i])
	{
		data->env_export[i] = ft_addstring("declare -x ", var_env_export(data->copy_env[i]));
		i++;
	}
	data->env_export[i] = NULL;
    data->new_copy_env = copy_tab(data->copy_env);
}

void    ft_export(t_cmds *cmd)
{
	int	i;

	i = 1;
	while (cmd->tab[i])
	{
		init_new_env(cmd, i);
		i++;
	}
}

/*
void    ft_export(t_cmds *cmd)
{
    char    *s;
    s = find_variable(cmd);	
	if (s && same_variable(cmd, s) == 1)
	{
	    change_env(cmd, s);
		return ;
	}
    if (s)
    	cmd->data->new_copy_env = init_new_env(cmd);
}
*/
