/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_replace_env2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:39:19 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/16 22:49:56 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*special_env(char c)
{
	int		cmd_sig;
	char	*str;

	cmd_sig = g_sig % 255;
	if (c == '?')
	{
		str = ft_itoa(cmd_sig);
		return (str);
	}
	else
		return (NULL);
}
