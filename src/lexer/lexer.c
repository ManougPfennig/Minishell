/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:32:31 by mapfenni          #+#    #+#             */
/*   Updated: 2023/11/30 17:18:16 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../minishell.h"

int	is_token(char word[2])
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

int	add_word(t_lexer **lexer, char *str, int token)
{
	t_copy	copy;
	t_lexer	*new;
	char	*word;

	copy.i = 0;
	copy.y = 0;
	while(is_token(str[copy.i]) && str[copy.i])
		copy.i++;
	copy.start = copy.i;
	while(!is_token(str[copy.i]) && str[copy.i] && copy.len++)
		copy.i++;
	word = malloc((copy.len + 1) * sizeof(char));
	word[copy.len] = '\0';
	while (--copy.len)
	{
		word[copy.y] = str[copy.start];
		
	}
	return (copy.i);
}

t_lexer	*lexer(char *str)
{
	int		i;
	t_lexer	**lexer;
	char	word[2];

	i = 0;
	lexer = malloc(sizeof(t_lexer *));
	while (str[i])
	{
		word[0] = str[i];
		word[1] = str[i + 1];
		if (is_token(word))
			i += add_word(lexer, str + i, is_token(word));
		else
			i++;
	}
}