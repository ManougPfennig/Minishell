/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:54:58 by nicolas           #+#    #+#             */
/*   Updated: 2024/01/18 14:12:21 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count(char *src)
{
	int	i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		i++;
	}
	return (0);
}

char	**copy_tab(char **tab)
{
	char	**copy;
	int		i;

	i = 0;
	if (tab == NULL)
		return (NULL);
	copy = malloc(sizeof(char *) * (len_tab(tab) + 1));
	while (tab && tab[i])
	{
		copy[i] = ft_strdup(tab[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	there_is_egual(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	len_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab[i])
	{
		while (tab[i])
			i++;
		return (i);
	}
	return (0);
}
