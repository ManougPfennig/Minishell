/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_working.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:55:37 by npatron           #+#    #+#             */
/*   Updated: 2024/01/16 21:55:44 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_patron_3000(t_env *ptr, char *name)
{
	while (ptr)
	{
		if (ft_strcmp(name, ptr->name))
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

	tab = NULL;
	ptr = data->copy_env;
	tab = ft_split(arg, '=');
	while (ptr)
	{
		if (ft_strcmp(tab[0], ptr->name) == 0)
		{
			if (tab[1] && has_equal(arg))
			{
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
