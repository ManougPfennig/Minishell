/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:32:31 by mapfenni          #+#    #+#             */
/*   Updated: 2023/12/04 19:31:19 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../incl/minishell.h"

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

char	*copy_word(char *str)
{
	t_copy	copy;
	char	*word;

	copy.i = 0;
	copy.y = 0;
	copy.len = 0;
	while(is_token(str[copy.i]) && str[copy.i])
		copy.i++;
	copy.start = copy.i;
	while(!is_token(str[copy.i]) && str[copy.i] && ++copy.len)
		copy.i++;
	word = malloc((copy.len + 1) * sizeof(char));
	word[copy.len] = '\0';
	while (copy.len)
	{
		word[copy.y] = str[copy.start];
		copy.y++;
		copy.start++;
		copy.len--;
	}
	return (word);
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
	new->str = copy_word(str);
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
	char			word[2];
	struct s_lexer	**lexer;

	i = 0;
	lexer = malloc(1 * sizeof(struct s_lexer *));
	*lexer = NULL;
	add_word(lexer, str + i, what_token(word));
	while (str[i])
	{
		word[0] = str[i];
		word[1] = str[i + 1];
		if (what_token(word))
			i += add_word(lexer, str + i, what_token(word));
		i++;
	}
	return (lexer);
}