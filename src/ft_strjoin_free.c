/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:35:54 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/04 20:23:16 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	to_free(char *s1, char *s2, int val)
{
	if (val == 1 && s1)
		free(s1);
	if (val == 2 && s2)
		free(s2);
	if (val == 3)
	{
		if (s1)
			free(s1);
		if (s2)
			free(s2);
	}
}

char	*ft_strjoin_free(char const *s1, char const *s2, int val)
{
	int		i;
	int		j;
	int		length;
	char	*dest;

	i = 0;
	j = 0;
	length = 0;
	while (s1 && s1[i++])
		length++;
	while (s2 && s2[j++])
		length++;
	i = 0;
	j = 0;
	dest = malloc((length + 1) * sizeof(char));
	if (!(dest))
		return (NULL);
	dest[length] = '\0';
	while (s1 && s1[i])
		dest[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		dest[j++] = s2[i++];
	to_free((char *)s1, (char *)s2, val);
	return (dest);
}
