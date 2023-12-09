/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:31:15 by mapfenni          #+#    #+#             */
/*   Updated: 2023/12/09 11:40:13 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_envchar(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= '_')
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
	while (is_envchar(str[i]) && ++len)
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

char	*to_env(char *str, int i)
{
	char	*name;
	char	*value;
	char	*new;

	new = NULL;
	name = keep_name(str + i);
	value = getenv(name);
	str[i - 1] = '\0';
	while (is_envchar(str[i]))
		i++;
	if (!value)
		value = "";
	new = ft_strjoin_free(value, str + i, 0);
	new = ft_strjoin_free(str, new, 2);
	free(str);
	free(name);
	return (new);
}

char	*replace_env(char *str)
{
	int		i;
	int		quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == 39 && quote == 0)
			quote = 1;
		else if (str[i] == 39 && quote == 1)
			quote = 0;
		if (str[i] == '$' && quote == 0)
		{
			if (is_envchar(str[i + 1]))
			{
				str = to_env(ft_strdup(str), i + 1);
				i--;
			}
		}
		i++;
	}
	return (str);
}
