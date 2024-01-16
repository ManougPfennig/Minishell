/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_working.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:15:56 by npatron           #+#    #+#             */
/*   Updated: 2024/01/15 11:46:16 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_export(t_cmds *cmd, char *str)
{
	char	*compare;
	int		i;
	int		j;
	
	j = 0;
	i = 0;
	while (str[j] && str[j] != '=')
		j++;
	compare = ft_addstring("declare -x ", str);
	while (cmd->data->env_export[i])
	{
		if (ft_strncmp(compare, cmd->data->env_export[i], 11 + j) == 0)
		{
			cmd->data->env_export[i] = ft_addstring("declare -x ", var_env_export(str));
			return (1);
		}
		i++;		
	}
	return (0);	
}

int	same_change(t_cmds *cmd, char *str)
{
	char	*compare;
	int		i;
	int		j;
	
	j = 0;
	i = 0;
	while (str[j] && str[j] != '=')
		j++;
	compare = ft_addstring("declare -x ", str);
	while (cmd->data->env_export[i])
	{
		if (ft_strncmp(compare, cmd->data->env_export[i], ft_strlen(compare)) == 0
			&& there_is_egual(str) == 1)
			return (1);
		i++;		
	}
	return (0);	
}

void    add_export(t_cmds *cmd, char *str)
{
    char	**tab;
    int		i;

	i = 0;
	if (same_change(cmd, str) == 1)
		return ;
	if (check_var(str) == 1 || change_export(cmd, str) == 1)
		return ;
	tab = malloc(sizeof(char *) * (len_tab(cmd->data->env_export) + 2));
	while (cmd->data->env_export[i])
	{
		tab[i] = ft_strdup(cmd->data->env_export[i]);
		i++;
	}
    if (there_is_egual(str) == 0)
	    tab[i] = ft_addstring("declare -x ", var_env_export(str));
    else
	{
        tab[i] = ft_addstring("declare -x ", str);
	}
	i++;
	tab[i] = NULL;
    cmd->data->env_export = copy_tab(tab);
}