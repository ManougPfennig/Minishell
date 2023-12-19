/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:16:27 by mapfenni          #+#    #+#             */
/*   Updated: 2023/12/19 01:34:52 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// is_in permet au programme de savoir quand il est dans des quote et
// conserver son type ( " ou ' ) lorsqu'il fait défiler la string.

void	is_in(char *in, char c)
{
	if (c == '"' || c == '\'')
	{
		if (*in == 0)
			*in = c;
		else if (*in == c)
			*in = 0;
	}
}

// word_number sert à déterminer d'avance le nombre de word qui seront
//r écupéré à partir de la string afin d'allouer le tableau "split".

int	word_number(char *str)
{
	int		i;
	int		word;
	char	in;

	i = 0;
	word = 0;
	in = 0;
	is_in(&in, str[i]);
	while (str[i])
	{
		while (str[i] && is_wspace(str[i]) && !in)
		{
			i++;
			is_in(&in, str[i]);
		}
		if (str[i] != '\0')
			word++;
		while (str[i] && (!is_wspace(str[i]) || in))
		{
			i++;
			is_in(&in, str[i]);
		}
	}
	return (word);
}

// quote_copy_word contribue à fill_tab en faisant la copie du début
// de la string donné et détermine sa fin.

char	*quote_copy_word(char *dest, char *str)
{
	int		i;
	int		j;
	char	in;

	i = 0;
	j = 0;
	in = 0;
	is_in(&in, str[0]);
	while (str[i + j] && (!is_wspace(str[i + j]) || in))
	{
		j++;
		is_in(&in, str[i + j]);
	}
	dest = malloc((j + 1) * sizeof(char));
	dest[j] = '\0';
	while (i != j)
	{
		dest[i] = str[i];
		i++;
	}
	return (dest);
}

// fill_tab determine le morceau de string qui correspond à un word,
// copie ce morceau grâce à quote_copy_word et le stock dans le tableau split.

void	fill_tab(char **split, char *str)
{
	int		i;
	int		word;
	char	in;

	i = 0;
	word = 0;
	in = 0;
	is_in(&in, str[i]);
	while (str[i])
	{
		while (str[i] && is_wspace(str[i]) && !in)
		{
			i++;
			is_in(&in, str[i]);
		}
		if (str[i] != '\0')
		{
			split[word] = quote_copy_word(split[word], str + i);
			word++;
		}	
		while (str[i] && (!is_wspace(str[i]) || in))
		{
			i++;
			is_in(&in, str[i]);
		}
	}
}

// lexer_split_quote va d'abord determiner le nombre de mots présent dans la string
// en la faisant défiler dans word_number.
// La séparation se fera ensuite sur les whitespaces (qui seront supprimé) et
// uniquement si ils ne sont pas dans des quotes.

char	**lexer_split_quote(char *str)
{
	int		tab_len;
	char	**tab;

	if (!str)
		return (NULL);
	tab_len = word_number((char *)str);
	tab = (char **)malloc(sizeof(char *) * (tab_len + 1));
	if (!tab)
		return (NULL);
	tab[tab_len] = 0;
	fill_tab(tab, (char *)str);
	return (tab);
}
