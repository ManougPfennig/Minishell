/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:48:54 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/18 19:36:18 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* change_g_sig_to() est la manifestation de ce a quoi la norme nous pousse,
elle permet de changer la valeur de g_sig et de return(1), pour la mettre
efficacement dans un if() et gagner trois lignes...*/

int	change_g_sig_to(int i)
{
	g_sig = i;
	return (1);
}

long long	ft_atoill(char *str)
{
	int			i;
	long long	ret;

	i = 0;
	ret = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		ret *= 10;
		ret += str[i] - '0';
		i++;
	}
	if (str[0] == '-')
		ret *= -1;
	return (ret);
}
