/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:48:54 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/18 21:18:57 by mapfenni         ###   ########.fr       */
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

int	putstr_fd(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	return (1);
}

int	putstr_fd_str(char *str, char *word, char *str2, int fd)
{
	if (str)
		ft_putstr_fd(str, fd);
	if (word)
		ft_putstr_fd(word, fd);
	if (str2)
		ft_putstr_fd(str2, fd);
	return (1);
}

int	putstr_fd_char(char *str, char c, char *str2, int fd)
{
	if (str)
		ft_putstr_fd(str, fd);
	if (c)
		ft_putchar_fd(c, fd);
	if (str2)
		ft_putstr_fd(str2, fd);
	return (1);
}
