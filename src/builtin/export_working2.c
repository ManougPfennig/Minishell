/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_working2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:38:41 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/18 21:39:22 by mapfenni         ###   ########.fr       */
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
