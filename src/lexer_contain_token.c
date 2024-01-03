/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_contain_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:56:44 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/03 20:20:08 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// is_token détermine si il s'agit d'un charactère de type token

int	is_token(char c)
{
	if (c == '<')
		return (LESS_THAN);
	if (c == '>')
		return (MORE_THAN);
	if (c == '|')
		return (PIPE);
	return (0);
}

// has_token détermine si une string contient un token

int	has_token(char *str)
{
	int		i;
	char	in;

	i = 0;
	in = 0;
	while (str[i])
	{
		is_in(&in, str[i]);
		if (is_token(str[i]) && !in)
			return (1);
		i++;
	}
	return (0);
}

// copy_token détecte le token et le copie dans new

char	*copy_token(char *str, int type)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_calloc(3, sizeof(char));
	if (type == PIPE)
		new[i] = str[i];
	else
	{
		while (is_token(str[i]) == type && i < 2)
		{
			new[i] = str[i];
			i++;
		}
	}
	return (new);
}

// copy_word détecte le mot et le copie dans new

char	*copy_word(char *str)
{
	int		i;
	char	in;
	char	*new;

	i = 0;
	in = 0;
	is_in(&in, str[i]);
	while ((!is_token(str[i]) || in) && str[i])
	{
		i++;
		is_in(&in, str[i]);
	}
	new = ft_calloc(i + 1, sizeof(char));
	i = 0;
	in = 0;
	is_in(&in, str[i]);
	while ((!is_token(str[i]) || in) && str[i])
	{
		new[i] = str[i];
		i++;
		is_in(&in, str[i]);
	}
	return (new);
}

/*contain_quote est un fonction qui va déterminer, malgré l'absence d'espaces
pour les séparer du reste du mot, si des tokens se situent dans ce mot.
L'objectif est de séparer ces tokens, les copier individuellement dans de
nouvelles strin et notamment copier le reste.
Le tout est stocké dans de nouvelles structures ajoutées à la suite de la
liste chaînée du lexer.*/

int	contain_token(t_lexer **lexer, char *str)
{
	int		i;
	char	in;
	char	*temp;

	i = 0;
	in = 0;
	is_in(&in, str[i]);
	while (str[i])
	{
		if (!in && is_token(str[i]))
		{
			temp = copy_token(str + i, is_token(str[i]));
			add_word(lexer, temp, what_token(temp));
			i += ft_strlen(temp);
		}
		else if (in || !is_token(str[i]))
		{
			temp = copy_word(str + i);
			add_word(lexer, temp, what_token(temp));
			i += ft_strlen(temp);
			in = 0;
		}
	}
	return (1);
}
