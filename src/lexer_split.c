/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:08:48 by mapfenni          #+#    #+#             */
/*   Updated: 2023/12/14 23:53:38 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_quote(t_quote *qu)
{
	if (qu->type || qu->dq || qu->q)
		return (1);
	return (0);
}

int	change_quote(t_quote *qu, char c)
{
	if (qu->dq == 0 && c == 34 && qu->type == 0)
	{
		qu->dq = 1;
		qu->type = 2;
	}
	else if (qu->dq == 1 && c == 34 && qu->type == 2)
	{
		qu->dq = 0;
		qu->type = 0;
	}
	if (qu->q == 0 && c == 39 && qu->type == 0)
	{
		qu->q = 1;
		qu->type = 1;
	}
	else if (qu->q == 1 && c == 39 && qu->type == 1)
	{
		qu->q = 0;
		qu->type = 0;
	}
	return (1);
}

int	word_number(char *str, t_quote *qu)
{
	int		i;
	int		number;

	i = 0;
	number = 0;
	while (str[i])
	{
		while (is_wspace(str[i]) && !qu->dq && !qu->q)
			i++;
		if (str[i] && change_quote(qu, str[i]))
			number++;
		while (str[i] && (!is_wspace(str[i]) || in_quote(qu)))
		{
			i++;
			change_quote(qu, str[i]);
		}
	}
	return (number);
}

char	*cp_word(char *dest, char *str, int j)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
//	if ((str[i]== 34 && str[0] == 34) || (str[i] == 39 && str[i] == 39))
//		i++;
	while (j)
	{
//		if ((str[i]== 34 && str[0] == 34) || (str[i] == 39 && str[i] == 39))
//			break ;
		dest[i2] = str[i];
		i2++;
		i++;
		j--;
	}
	dest[i] = '\0';
	return (dest);
}

void	fill_tab(char **split, char *str, t_quote *qu)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (is_wspace(str[i]) && !in_quote(qu))
			i++;
		else
		{
			j = 0;
			while (str[i + j] && (!is_wspace(str[i + j]) || in_quote(qu)) && change_quote(qu, str[i]))
				j++;
			split[count] = (char *)malloc(sizeof(char) * (j + 1));
			cp_word(split[count], str + i, j);
			i = i + j;
			count++;
		}
	}
}

char	**split_quote_wspace(char *str)
{
	int		tab_len;
	char	**tab;
	t_quote	qu;

	if (!str)
		return (NULL);
	qu.dq = 0;
	qu.q = 0;
	qu.type = 0;
	tab_len = word_number((char *)str, &qu);
	tab = (char **)malloc(sizeof(char *) * (tab_len + 1));
	if (!tab)
		return (NULL);
	tab[tab_len] = NULL;
	qu.dq = 0;
	qu.q = 0;
	qu.type = 0;
	fill_tab(tab, (char *)str, &qu);
	return (tab);
}

/*char	*copy_word(char *dest, char *str, int j)
{
	int	i;
	int	i2;
	t_quote	qu;

	i = 0;
	i2 = 0;
	while (j)
	{
		change_quote(&qu, str[i]);
		if (qu.type == 1 && str[i] == '\'' && change_quote(&qu, str[i]))
			i++;
		else if (qu.type == 2 && str[i] == '\"' && change_quote(&qu, str[i]))
			i++;
		else
		{
			dest[i2] = str[i];
			i2++;
			i++;
		}
		j--;
	}
	dest[i] = '\0';
	return (dest);
}*/