/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_working.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:16:58 by nicolas           #+#    #+#             */
/*   Updated: 2024/01/18 19:26:07 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}

int	str_is_digit(char *str)
{
	int			i;
	long long	ll;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (is_digit(str[i]) == 1)
			return (1);
		i++;
	}
	ll = ft_atoill(str);
	if (ll > INT_MAX || ll < INT_MIN)
		return (1);
	return (0);
}

int	ft_exit(t_cmds *cmd)
{
	ft_putstr_fd("exit\n", 2);
	if (cmd->tab[1] == NULL)
		return (0);
	else if (cmd->tab[2] == NULL)
	{
		if (str_is_digit(cmd->tab[2]))
		{
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(cmd->tab[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (2);
		}
		else
			return (ft_atoi(cmd->tab[1]));
	}
	else
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}
