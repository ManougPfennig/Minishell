/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_replace_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:31:15 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/15 20:23:32 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_envchar(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c == '_' || c == '?')
		return (1);
	return (0);
}

int	is_simple_envchar(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

char	*keep_name(char *str)
{
	char	*name;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (is_simple_envchar(str[i]) && ++len)
		i++;
	name = ft_calloc((len + 1), sizeof(char));
	i = 0;
	while (i != len)
	{
		name[i] = str[i];
		i++;
	}
	return (name);
}

char	*to_env(t_data *data, char *str, int i)
{
	char	*name;
	char	*value;
	char	*new;

	new = NULL;
	name = keep_name(str + i);
	if ((str[i] >= '0' && str[i] <= '9') || (str[i] == '?'))
		value = special_env(str[i]);
	else
		value = find_env_patron(data, name);
	str[i - 1] = '\0';
	if ((str[i] >= '0' && str[i] <= '9') || (str[i] == '?'))
		i++;
	else
		while (is_simple_envchar(str[i]))
			i++;
	if (!value)
		value = "";
	new = ft_strjoin_free(value, str + i, 0);
	new = ft_strjoin_free(str, new, 2);
	free(str);
	free(name);
	if (ft_strlen(new) == 0)
	{
		free(new);
		new = NULL;
	}
	return (new);
}

// replace_env va trouver tout les $ (hors simple quote) puis
// vérifier si le nom qui suit correspond bien à ce qui peut être attribué
// comme nom à une variable env. Dans le cas échéant, la string est ensuite
// découpée pour récupérer le nom complet puis recollée avec la
// valeur de remplacement récupérée grâce à getenv().
// Dans le cas des $ suivi d'un numéro, il retire la partie env de la string.

char	*replace_env(t_data *data, char *str)
{
	int		i;
	char	in;

	i = 0;
	in = 0;
	while (str && str[i])
	{
		is_in(&in, str[i]);
		if (str[i] == '$' && in != '\'')
		{
			if ((str[i + 1] == '\"' || str[i + 1] == '\'') && !in)
				move_back(str + i);
			else if (is_envchar(str[i + 1]))
			{
				str = to_env(data, ft_strdup(str), i + 1);
				i--;
			}
		}
		i++;
	}
	return (str);
}
