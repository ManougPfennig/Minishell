/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:08:48 by mapfenni          #+#    #+#             */
/*   Updated: 2023/12/24 16:52:37 by mapfenni         ###   ########.fr       */
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

char	remove_excess_quote(char *str)
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
			while (in && str[i])
			{
				is_in(&in, str[i]);
				if (in)
					i++;
			}
			move_back(str + i);
		}
	}
	return (in);
}

// récupère la string donné au prompt avec readline, et sépare les mots en
// fonction des whitespaces et quotes et retire les quotes de trop.
// - la première séparation se déroule dans lexer_split_quote
// - remove_excess_quote va supprimer les quotes délimiteurs et laisser celles
// qui font réellement parti du mot.

struct s_lexer	**split_quote_wspace(char *str)
{
	int				i;
	char			**tab;
	struct s_lexer	**lexer;

	i = 0;
	if (!str)
		return (NULL);
	lexer = malloc(1 * sizeof(struct s_lexer *));
	*lexer = NULL;
	tab = lexer_split_quote(str);
	while (tab[i])
	{
		add_word(lexer, ft_strdup(tab[i]), what_token(tab[i]));
		i++;
	}
	ft_free_tab(tab, NULL);
	return (lexer);
}
