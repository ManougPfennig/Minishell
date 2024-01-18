/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_working.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:16:58 by nicolas           #+#    #+#             */
/*   Updated: 2024/01/18 14:08:20 by mapfenni         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_digit(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_cmds *cmd)
{
	int	i;

	i = 0;
	while (cmd->tab[i])
		i++;
	write(1, "exit\n", 5);
	if (cmd->tab[1] && str_is_digit(cmd->tab[1]) == 0
		&& i > 2)
	{
		write(1, "minishell: exit: too many arguments\n", 37);
		exit(EXIT_FAILURE);
	}
	if ((cmd->tab[1] && str_is_digit(cmd->tab[1]) == 1))
	{
		write(1, "minishell: exit: ", 18);
		write(1, cmd->tab[1], ft_strlen(cmd->tab[1]));
		write(1, ": numeric argument required\n", 28);
		exit(EXIT_FAILURE);
	}
}
