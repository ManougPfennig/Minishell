/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_working.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:16:58 by nicolas           #+#    #+#             */
/*   Updated: 2024/01/26 01:02:11 by mapfenni         ###   ########.fr       */
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
	if (!str)
		return (0);
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

int	will_exit_and_ret(t_cmds *cmd, int exit, int ret)
{
	if (exit == 1)
		cmd->data->exit = 1;
	if (cmd->next || cmd->prev)
		cmd->data->exit = 0;
	if (ret == 0)
		ret = g_sig;
	return (ret);
}

int	ft_exit(t_cmds *cmd)
{
	if (cmd->tab[1] == NULL)
		return (will_exit_and_ret(cmd, 1, 0));
	else if (str_is_digit(cmd->tab[1]) == 0 && cmd->tab[2] == NULL)
		return (will_exit_and_ret(cmd, 1, ft_atoi(cmd->tab[1]) % 256));
	else if (str_is_digit(cmd->tab[1]))
	{
		putstr_fd_str("bash: exit: ", cmd->tab[1], ": numeric argument \
required\n", 2);
		return (will_exit_and_ret(cmd, 1, 2));
	}
	else if (str_is_digit(cmd->tab[1]) == 0 && cmd->tab[2])
	{
		if (!cmd->prev && !cmd->next)
			ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}
