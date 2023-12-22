/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:08:48 by mapfenni          #+#    #+#             */
/*   Updated: 2023/12/22 17:55:12 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// retire le premier char de la string, en l'occurence ici est utilisé afin
// de retirer les quotes visé, de manière simple.

void	move_back(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
}

// fais défiler la string pour supprimer les quotes qui doivent être
// retiré pour récupérer le mot final (en prenant en compte env)

void	remove_excess_quote(char *str)
{
	int		i;
	char	in;

	i = 0;
	in = 0;
	while (str[i])
	{
		is_in(&in, str[i]);
		if (!in)
			i++;
		else if (str[i])
		{
			move_back(str + i);
			while (in)
			{
				i++;
				is_in(&in, str[i]);
			}
			move_back(str + i);
		}
	}
}

// récupère la string donné au prompt avec readline, et sépare les mots en
// fonction des whitespaces et quotes et retire les quotes de trop.
// - la première séparation se déroule dans lexer_split_quote
// - remove_excess_quote va supprimer les quotes délimiteurs et laisser celles
// qui font réellement parti de la string

char	**split_quote_wspace(char *str)
{
	char	**tab;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	tab = lexer_split_quote(str);
	while (tab[i])
	{
		tab[i] = replace_env(tab[i]);
		remove_excess_quote(tab[i]);
		i++;
	}
	return (tab);
}
