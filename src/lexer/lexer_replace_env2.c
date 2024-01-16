/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_replace_env2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:39:19 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/16 20:30:31 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*special_env(char c)
{
	int		cmd_sig;
	char	*str;

	cmd_sig = g_sig % 255;
	if (c == '?')
	{
		str = ft_itoa(cmd_sig);
		return (str);
	}
	else
	{
//		str = ft_strdup("");
//		return (str);
		return (NULL);
	}
}

char	*find_env_patron(t_data *data, char *name)
{
	char	**tab;
	char	*value;
	int		i;

	i = 0;
	tab = NULL;
	while(data->copy_env[i])
	{
		tab = ft_split(data->copy_env[i], '=');
		if (ft_strcmp(tab[0], name) == 0 && tab[1])
		{
			value = tab[1];
			free(tab[0]);
			free(tab);
			return (value);
		}
		else
			ft_free_tab(tab, NULL);
		i++;
	}
//	return (ft_strdup(""));
	return (NULL);
}
