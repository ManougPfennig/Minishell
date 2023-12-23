/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:32:31 by mapfenni          #+#    #+#             */
/*   Updated: 2023/12/23 14:19:12 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//detecte la présence possible d'un token

int	is_token(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

// determine le token en question et renvoie une valeure attribuée

int	what_token(char word[2])
{
	if (word[0] == '<' && word[1] == '<')
		return (LESS_LESS);
	if (word[0] == '>' && word[1] == '>')
		return (MORE_MORE);
	if (word[0] == '<')
		return (LESS_THAN);
	if (word[0] == '>')
		return (MORE_THAN);
	if (word[0] == '|')
		return (PIPE);
	return (0);
}

// renvoie le dernier chaînon de la liste chaînée

struct s_lexer	*ft_last_link(struct s_lexer **lexer)
{
	struct s_lexer	*link;

	link = *lexer;
	if (link)
	{
		while (link->next != NULL)
			link = link->next;
	}
	return (link);
}

// ajoute un word à la liste chaînée renvoyée par le lexer

int	add_word(struct s_lexer **lexer, char *str, int token)
{
	struct s_lexer	*new;

	new = malloc(1 * sizeof(struct s_lexer));
	new->str = str;
	new->token = token;
	new->next = NULL;
	if (lexer[0] == NULL)
		lexer[0] = new;
	else
	{
		new->prev = ft_last_link(lexer);
		ft_last_link(lexer)->next = new;
	}
	return (ft_strlen(new->str));
}

/*lexer est là pour la première transformation de la string passé
dans le prompt donné par readline. Elle va d'abord séparer cette
string en "words", qui constitue les différentes parties de la
ligne de commande, notant si telle ou telle est un token et en
interprétant les quotes.*/

// note : doit fix les mots vide du style ""

struct s_lexer	**lexer(char *str)
{
	int				i;
	char			word[2];
	char			**tab;
	struct s_lexer	**lexer;

	i = 0;
	lexer = malloc(1 * sizeof(struct s_lexer *));
	*lexer = NULL;
	tab = split_quote_wspace(str);
	while (tab[i])
	{
		word[0] = tab[i][0];
		word[1] = tab[i][1];
		add_word(lexer, tab[i], what_token(word));
		i++;
	}
	return (lexer);
}
