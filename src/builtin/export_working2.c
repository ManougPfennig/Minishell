/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_working2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:38:41 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/25 22:40:03 by npatron          ###   ########.fr       */
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

int	has_something_after_equal(char *s)
{
	int	i;

	i = 0;
	if (!has_equal(s))
		return (0);
	while (s[i] != '=')
		i++;
	if (s[i + 1])
		return (1);
	return (0);
}

char	*before_equal(char *s)
{
	char	*line;
	int		i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i] && s[i] != '=')
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	**recup_tab(char *s)
{
	char	**result;
	int		i;

	i = 0;
	if (has_something_after_equal(s))
		result = malloc(sizeof(char *) * 3);
	else
		result = malloc(sizeof(char *) * 2);
	result[0] = before_equal(s);
	while (s[i] && s[i] != '=')
		i++;
	if (has_something_after_equal(s))
	{
		result[1] = ft_strdup(s + i + 1);
		result[2] = NULL;
	}
	else
		result[1] = NULL;
	return (result);
}

