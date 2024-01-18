/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_working.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:55:37 by npatron           #+#    #+#             */
/*   Updated: 2024/01/18 17:36:20 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_patron_3000(t_env *ptr, char *name)
{
	while (ptr)
	{
		if (ft_strcmp(name, ptr->name) == 0)
			return (ft_strdup(ptr->value));
		ptr = ptr->next;
	}
	return (ft_strdup(""));
}

int	has_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	modify_export(t_data *data, char *arg)
{
	t_env	*ptr;
	char	**tab;

	ptr = data->copy_env;
	tab = ft_split(arg, '=');
	while (ptr)
	{
		if (ft_strcmp(tab[0], ptr->name) == 0)
		{
			if (has_equal(arg))
			{
				ptr->equal = 1;
				free(ptr->value);
				if (tab[1])
					ptr->value = ft_strdup(tab[1]);
				else
					ptr->value = ft_strdup("");
			}
			ft_free_tab(tab, NULL);
			return ;
		}
		if (ptr->next == NULL)
		{
			env_lst_addback(data, env_lst_new(arg));
			return ;
		}
		ptr = ptr->next;
	}
	ft_free_tab(tab, NULL);
}

void	print_export(t_cmds *cmd)
{
	t_env	*ptr;

	ptr = cmd->data->copy_env;
	while (ptr)
	{
		write(1, "declare -x ", 12);
		write(1, ptr->name, ft_strlen(ptr->name));
		if (ptr->equal)
		{
			write(1, "=", 1);
			write(1, "\"", 1);
			write(1, ptr->value, ft_strlen(ptr->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		ptr = ptr->next;
	}
}

int	ft_export(t_cmds *cmd)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (!cmd->tab[1])
	{
		print_export(cmd);
		return (0);
	}
	while (cmd->tab[i])
	{
		if (check_var(cmd->tab[i]) == 0)
			modify_export(cmd->data, cmd->tab[i]);
		else
			ret = 1;
		i++;
	}
	return (ret);
}
