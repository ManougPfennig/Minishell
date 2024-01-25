/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:46:19 by npatron           #+#    #+#             */
/*   Updated: 2024/01/23 19:17:51 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_env(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		env_lst_addback(data, env_lst_new(env[i]));
		i++;
	}
	return (i);
}

t_env	*env_lst_new(char *env)
{
	t_env	*new;
	char	**tab;

	new = malloc(sizeof(t_env));
	new->name = NULL;
	new->value = NULL;
	new->equal = 0;
	new->rank = 0;
	if (has_equal(env))
		new->equal = 1;
	tab = ft_split(env, '=');
	new->name = ft_strdup(tab[0]);
	if (tab[1])
		new->value = ft_strdup(tab[1]);
	else
		new->value = ft_strdup("");
	new->prev = NULL;
	new->next = NULL;
	ft_free_tab(tab, NULL);
	return (new);
}

void	env_lst_addback(t_data *data, t_env *new)
{
	t_env	*ptr;

	ptr = data->copy_env;
	if (!data->copy_env)
	{
		data->copy_env = new;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
	new->prev = ptr;
	return ;
}

void	rank_name(t_data *data)
{
	t_env	*ptr;
	t_env	*ptr2;
	int		i;

	ptr = data->copy_env;
	while (ptr)
	{
		i = 0;
		ptr2 = data->copy_env;
		while (ptr2)
		{
			if (ft_strcmp(ptr->name, ptr2->name) > 0)
				i++;
			ptr2 = ptr2->next;
		}
		ptr->rank = i;
		ptr = ptr->next;
	}
}

