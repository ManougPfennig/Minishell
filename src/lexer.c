/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:32:31 by mapfenni          #+#    #+#             */
/*   Updated: 2023/12/14 23:54:02 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

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

struct s_lexer *ft_last_link(struct s_lexer **lexer)
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

struct s_lexer	**lexer(char *str)
{
	int				i;
	char			word[3];
	char			**tab;
	struct s_lexer	**lexer;

	i = 0;
	lexer = malloc(1 * sizeof(struct s_lexer *));
	*lexer = NULL;
	tab = split_quote_wspace(str);
	add_word(lexer, str + i, what_token(word));
	while (tab[i])
	{
		printf("word: %s\n", tab[i]);
		word[0] = tab[i][0];
		word[1] = tab[i][1];
		word[2] = tab[i][2];
		add_word(lexer, tab[i], what_token(word));
		i++;
	}
	return (lexer);
}
