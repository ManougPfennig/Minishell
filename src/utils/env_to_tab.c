/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:29:53 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/21 13:01:07 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	return ;
}

int	env_len(t_env *ptr)
{
	int	i;

	i = 0;
	while (ptr)
	{
		if (ptr->equal)
			i++;
		ptr = ptr->next;
	}
	return (i);
}

char	**env_to_tab(t_data	*data)
{
	char	**tab;
	t_env	*ptr;
	int		i;

	i = env_len(data->copy_env);
	tab = malloc((i + 1) * sizeof(char *));
	i = 0;
	ptr = data->copy_env;
	while (ptr)
	{
		if (ptr->equal)
		{
			tab[i] = ft_strjoin(ptr->name, "=");
			tab[i] = ft_strjoin_free(tab[i], ptr->value, 1);
			i++;
		}
		ptr = ptr->next;
	}
	tab[i] = NULL;
	return (tab);
}