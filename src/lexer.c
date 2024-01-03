/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:32:31 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/03 18:02:26 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// determine le token en question et renvoie une valeure attribuée

int	what_token(char *str)
{
	if (str[0] == '<' && str[1] == '<' && ft_strlen(str) == 2)
		return (LESS_LESS);
	if (str[0] == '>' && str[1] == '>' && ft_strlen(str) == 2)
		return (MORE_MORE);
	if (str[0] == '<' && ft_strlen(str) == 1)
		return (LESS_THAN);
	if (str[0] == '>' && ft_strlen(str) == 1)
		return (MORE_THAN);
	if (str[0] == '|' && ft_strlen(str) == 1)
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
	new->prev = NULL;
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
	char			in;
	struct s_lexer	*ptr;
	struct s_lexer	**lexer;

	if (ft_strlen(str) == 0)
		return (NULL);
	in = 0;
	lexer = split_quote_wspace(str);
	if (!lexer)
		return (NULL);
	ptr = *lexer;
	while (ptr)
	{
		ptr->str = replace_env(ptr->str);
		in = remove_excess_quote(ptr->str);
		if (in)
		{
			printf("Parsing error near '\\%c'\n", in);
			free_lexer(lexer);
			return (NULL);
		}
		ptr = ptr->next;
	}
	return (lexer);
}

// Une semaine pour comprendre comment gérer des quotes... ✺◟(•‿•)◞✺
